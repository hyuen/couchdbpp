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
#include <sstream>

#include "couchdb/Database.hpp"
#include "couchdb/Exception.hpp"

using namespace std;
using namespace CouchDB;

Database::Database(Communication &_comm, const string &_name)
   : comm(_comm)
   , name(_name)
{
}

Database::Database(const Database &db)
   : comm(db.comm)
   , name(db.name)
{
}

Database::~Database(){
}

Database& Database::operator=(Database &db){
   name = db.getName();
   return *this;
}

const string& Database::getName() const{
   return name;
}

vector<Document> Database::listDocuments(){
   Variant var = comm.getData("/" + name + "/_all_docs");
   Object  obj = boost::any_cast<Object>(*var);

   int numRows = boost::any_cast<int>(*obj["total_rows"]);

   vector<Document> docs;

   if(numRows > 0){
      Array rows = boost::any_cast<Array>(*obj["rows"]);

      Array::iterator        row     = rows.begin();
      const Array::iterator &row_end = rows.end();
      for(; row != row_end; ++row){
         Object docObj = boost::any_cast<Object>(**row);
         Object values = boost::any_cast<Object>(*docObj["value"]);

         Document doc(comm, name,
                      boost::any_cast<string>(*docObj["id"]),
                      boost::any_cast<string>(*docObj["key"]),
                      boost::any_cast<string>(*values["rev"]));

         docs.push_back(doc);
      }
   }

   return docs;
}

Document Database::getDocument(const string &id, const string &rev){
   string url = "/" + name + "/" + id;
   if(rev.size() > 0)
      url += "?rev=" + rev;

   Variant var = comm.getData(url);
   Object  obj = boost::any_cast<Object>(*var);

   if(obj.find("error") != obj.end())
      throw Exception("Document " + id + " (v" + rev + ") not found: " + boost::any_cast<string>(*obj["error"]));

   Document doc(comm, name,
                boost::any_cast<string>(*obj["_id"]),
                "", // no key returned here
                boost::any_cast<string>(*obj["_rev"])
               );

   return doc;
}

static string createJSON(const Variant &data){
   ostringstream ostr;
   ostr << data;
   return ostr.str();
}

Document Database::createDocument(const Variant &data, const string &id){
   vector<Attachment> attachments;
   return createDocument(data, attachments, id);
}

Document Database::createDocument(Variant data,
                                  vector<Attachment> attachments,
                                  const string &id){
   if(attachments.size() > 0){
      Object attachmentObj;

      vector<Attachment>::iterator attachment = attachments.begin();
      const vector<Attachment>::iterator &attachmentEnd = attachments.end();
      for(; attachment != attachmentEnd; ++attachment){
         Object attachmentData;
         attachmentData["content_type"] = createVariant(attachment->getContentType());
         attachmentData["data"        ] = createVariant(attachment->getData());
         attachmentObj[attachment->getID()] = createVariant(attachmentData);
      }

      Object obj          = boost::any_cast<Object>(*data);
      obj["_attachments"] = createVariant(attachmentObj);
      data                = createVariant(obj);
   }

   string json = createJSON(data);

   Variant var;
   if(id.size() > 0)
      var = comm.getData("/" + name + "/" + id, "PUT", json);
   else
      var = comm.getData("/" + name + "/", "POST", json);

   Object  obj = boost::any_cast<Object>(*var);

   if(obj.find("error") != obj.end())
      throw Exception("Document could not be created: " + boost::any_cast<string>(*obj["reason"]));

   Document doc(comm, name,
                boost::any_cast<string>(*obj["id"]),
                "", // no key returned here
                boost::any_cast<string>(*obj["rev"])
               );

   return doc;
}

ostream& operator<<(ostream &out, const CouchDB::Database &db){
   return out << "<Database: " << db.getName() << ">";
}
