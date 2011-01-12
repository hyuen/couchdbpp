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
#ifndef __COUCH_DB_DATABASE_HPP__
#define __COUCH_DB_DATABASE_HPP__

#include <string>
#include <iostream>

#include "couchdb/Document.hpp"

namespace CouchDB{

class Database{
   friend class Connection;

   protected:
      Database(Communication&, const std::string&);

   public:
      Database(const Database&);
      ~Database();

      Database& operator=(Database&);

      const std::string& getName() const;

      std::vector<Document> listDocuments();
      Document getDocument(const std::string&, const std::string &rev="");
      Document createDocument(const Variant&, const std::string &id="");
      Document createDocument(Variant, std::vector<Attachment>,
                              const std::string &id="");

   protected:
      Communication& getCommunication();

   private:
      Communication &comm;
      std::string   name;
};

}

std::ostream& operator<<(std::ostream&, const CouchDB::Database&);

#endif
