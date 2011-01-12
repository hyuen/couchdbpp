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
#ifndef __COUCH_DB_DOCUMENT_HPP__
#define __COUCH_DB_DOCUMENT_HPP__

#include <iostream>
#include <string>
#include <vector>

#include "couchdb/Revision.hpp"
#include "couchdb/Attachment.hpp"

namespace CouchDB{

class Document{
   friend class Database;

   protected:
      Document(Communication&, const std::string&,
               const std::string&, const std::string&, const std::string&);

   public:
      Document(const Document&);
      ~Document();

      Document& operator=(Document&);
      bool operator==(const Document&);

      const std::string& getID() const;
      const std::string& getKey() const;
      const std::string& getRevision() const;

      std::vector<Revision> getAllRevisions();

      Variant getData();

      bool addAttachment(const std::string&, const std::string&,
                         const std::string&);
      Attachment getAttachment(const std::string&);
      std::vector<Attachment> getAllAttachments();
      bool removeAttachment(const std::string&);

      Document copy(const std::string&, const std::string &rev = "");
      bool remove();

   protected:
      Communication& getCommunication();
      const std::string& getDatabase() const;

      std::string getURL(bool) const;

   private:
      Communication &comm;
      std::string   db;
      std::string   id;
      std::string   key;
      std::string   revision;
};

}

std::ostream& operator<<(std::ostream&, const CouchDB::Document&);

#endif
