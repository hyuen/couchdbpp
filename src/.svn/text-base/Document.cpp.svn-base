/**
 * Copyright 2009 Tragicphantom Productions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
**/
#include "couchdb/Document.hpp"
#include "couchdb/Exception.hpp"

using namespace std;
using namespace CouchDB;

Document::Document(Communication &_comm, const string &_db, const string &_id,
                   const string &_key, const string &_rev)
   : comm(_comm)
   , db(_db)
   , id(_id)
   , key(_key)
   , revision(_rev)
{
}

Document::Document(const Document &doc)
   : comm(doc.comm)
   , db(doc.db)
   , id(doc.id)
   , key(doc.key)
   , revision(doc.revision)
{
}

Document::~Document(){
}

Document& Document::operator=(Document& doc){
   db       = doc.getDatabase();
   id       = doc.getID();
   key      = doc.getKey();
   revision = doc.getRevision();

   return *this;
}

bool Document::operator==(const Document &doc){
   return (id == doc.getID());
}

Communication& Document::getCommunication(){
   return comm;
}

const string& Document::getDatabase() const{
   return db;
}

const string& Document::getID() const{
   return id;
}

const string& Document::getKey() const{
   return key;
}

const string& Document::getRevision() const{
   return revision;
}

string Document::getURL(bool withRevision) const{
   string url = "/" + getDatabase() + "/" + getID();
   if(withRevision && revision.size() > 0)
      url += "?rev=" + revision;
   return url;
}

vector<Revision> Document::getAllRevisions(){
   vector<Revision> revisions;

   Variant var = comm.getData(getURL(false) + "?revs_info=true");
   Object  obj = boost::any_cast<Object>(*var);

   Array revInfo = boost::any_cast<Array>(*obj["_revs_info"]);

   Array::iterator        revInfoItr = revInfo.begin();
   const Array::iterator &revInfoEnd = revInfo.end();
   for(; revInfoItr != revInfoEnd; ++revInfoItr){
      Object revObj    = boost::any_cast<Object>(**revInfoItr);
      revisions.push_back(Revision(boost::any_cast<string>(*revObj["rev"]),
                                   boost::any_cast<string>(*revObj["status"])));
   }

   return revisions;
}

Variant Document::getData(){
   Variant var = comm.getData(getURL(false));
   Object  obj = boost::any_cast<Object>(*var);

   if(obj.find("_id") == obj.end() && obj.find("_rev") == obj.end() &&
      obj.find("error") != obj.end() && obj.find("reason") != obj.end())
      throw Exception("Document '" + getID() + "' not found: " + boost::any_cast<string>(*obj["reason"]));

   return var;
}

bool Document::addAttachment(const string &attachmentId,
                             const string &contentType,
                             const string &data){
   string url = getURL(false) + "/" + attachmentId;
   if(revision.size() > 0)
      url += "?rev=" + revision;

   Communication::HeaderMap headers;
   headers["Content-Type"] = contentType;

   Variant var = comm.getData(url, headers, "PUT", data);
   Object  obj = boost::any_cast<Object>(*var);

   if(obj.find("error") != obj.end() && obj.find("reason") != obj.end())
      throw Exception("Could not create attachment '" + attachmentId + "': " + boost::any_cast<string>(*obj["reason"]));

   revision = boost::any_cast<string>(*obj["rev"]);

   return boost::any_cast<bool>(*obj["ok"]);
}

Attachment Document::getAttachment(const string &attachmentId){
   Object data = boost::any_cast<Object>(*getData());

   if(data.find("_attachments") == data.end())
      throw Exception("No attachments");

   Object attachments = boost::any_cast<Object>(*data["_attachments"]);
   if(attachments.find(attachmentId) == attachments.end())
      throw Exception("No attachment found with id '" + attachmentId + "'");

   Object attachment = boost::any_cast<Object>(*attachments[attachmentId]);

   return Attachment(comm, db, id, attachmentId, "", boost::any_cast<string>(*attachment["content_type"]));
}

vector<Attachment> Document::getAllAttachments(){
   Object data = boost::any_cast<Object>(*getData());

   if(data.find("_attachments") == data.end())
      throw Exception("No attachments");

   vector<Attachment> vAttachments;

   Object attachments = boost::any_cast<Object>(*data["_attachments"]);

   Object::iterator attachmentItr = attachments.begin();
   const Object::iterator &attachmentEnd = attachments.end();
   for(; attachmentItr != attachmentEnd; ++attachmentItr){
      const string &attachmentId = attachmentItr->first;
      Object attachment = boost::any_cast<Object>(*attachmentItr->second);

      vAttachments.push_back(Attachment(comm, db, id, attachmentId, "",
                                        boost::any_cast<string>(*attachment["content_type"])));
   }

   return vAttachments;
}

bool Document::removeAttachment(const string &attachmentId){
   string url = getURL(false) + "/" + attachmentId;
   if(revision.size() > 0)
      url += "?rev=" + revision;

   Variant var = comm.getData(url, "DELETE");
   Object  obj = boost::any_cast<Object>(*var);

   if(obj.find("error") != obj.end() && obj.find("reason") != obj.end())
      throw Exception("Could not delete attachment '" + attachmentId + "': " + boost::any_cast<string>(*obj["reason"]));

   revision = boost::any_cast<string>(*obj["rev"]);

   return boost::any_cast<bool>(*obj["ok"]);
}

Document Document::copy(const string &targetId, const string &targetRev){
   Communication::HeaderMap headers;
   if(targetRev.size() > 0)
      headers["Destination"] = targetId + "?rev=" + targetRev;
   else
      headers["Destination"] = targetId;

   Variant var = comm.getData(getURL(true), headers, "COPY");
   Object  obj = boost::any_cast<Object>(*var);

   if(obj.find("error") != obj.end() && obj.find("reason") != obj.end())
      throw Exception("Could not copy document '" + getID() + "' to '" + targetId + "': " + boost::any_cast<string>(*obj["reason"]));

   string newId = targetId;
   if(obj.find("id") != obj.end())
      newId = boost::any_cast<string>(*obj["id"]);

   return Document(comm, db, newId, "",
                   boost::any_cast<string>(*obj["rev"]));
}

bool Document::remove(){
   Variant var = comm.getData(getURL(true), "DELETE");
   Object  obj = boost::any_cast<Object>(*var);

   return boost::any_cast<bool>(*obj["ok"]);
}

ostream& operator<<(ostream &out, const CouchDB::Document &doc){
   return out << "{id: " << doc.getID() << ", key: " << doc.getKey() << ", rev: " << doc.getRevision() << "}";
}
