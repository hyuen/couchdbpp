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
#include "couchdb/Attachment.hpp"
#include "couchdb/Exception.hpp"

using namespace std;
using namespace CouchDB;

Attachment::Attachment(Communication &_comm, const string &_db,
                       const string &_document, const string &_id,
                       const string &_revision, const string &_contentType)
   : comm(_comm)
   , db(_db)
   , document(_document)
   , id(_id)
   , revision(_revision)
   , contentType(_contentType)
{
}

Attachment::Attachment(const Attachment &attachment)
   : comm(attachment.comm)
   , db(attachment.db)
   , document(attachment.document)
   , id(attachment.id)
   , revision(attachment.revision)
{
}

Attachment::~Attachment(){
}

Attachment& Attachment::operator=(Attachment &attachment){
   comm     = attachment.comm;
   db       = attachment.db;
   document = attachment.document;
   id       = attachment.id;
   revision = attachment.revision;

   return *this;
}

const string& Attachment::getID() const{
   return id;
}

const string& Attachment::getRevision() const{
   return revision;
}

const string& Attachment::getContentType() const{
   return contentType;
}

string Attachment::getData(){
   string data;

   if(rawData.size() > 0)
      data = rawData;
   else{
      string url = "/" + db + "/" + document + "/" + id;
      if(revision.size() > 0)
         url += "?rev=" + revision;
      data = comm.getRawData(url);

      if(data.size() > 0 && data[0] == '{'){
         // check to make sure we did not receive an error
         Object obj = boost::any_cast<Object>(*comm.getData(url));
         if(obj.find("error") != obj.end() && obj.find("reason") != obj.end())
            throw Exception("Could not retrieve data for attachment '" + id + "': " + boost::any_cast<string>(*obj["reason"]));
      }
   }

   return data;
}

ostream& operator<<(ostream &out, const CouchDB::Attachment &attachment){
   return out << "{id: " << attachment.getID()
              << ", rev: " << attachment.getRevision()
              << ", content-type: " << attachment.getContentType()
              << "}";
}
