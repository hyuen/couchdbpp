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
#ifndef __COUCH_DB_CONNECTION_HPP__
#define __COUCH_DB_CONNECTION_HPP__

#include <string>
#include <vector>

#include "couchdb/Exception.hpp"
#include "couchdb/Database.hpp"
#include "couchdb/Communication.hpp"

namespace CouchDB{

class Connection{
   public:
      Connection();
      Connection(const std::string&);
      ~Connection();

      std::string getCouchDBVersion() const;

      std::vector<std::string> listDatabases();
      Database getDatabase(const std::string&);

      bool createDatabase(const std::string&);
      bool deleteDatabase(const std::string&);

   private:
      void init(const std::string&);
      void getInfo();

      Communication comm;
      std::string   couchDBVersion;
};

}

#endif
