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
#ifndef __COUCH_DB_REVISION_HPP__
#define __COUCH_DB_REVISION_HPP__

#include <iostream>
#include <string>

namespace CouchDB{

class Revision{
   public:
      Revision(const std::string&, const std::string&);
      Revision(const Revision&);
      ~Revision();

      const std::string& getVersion() const;
      const std::string& getStatus() const;

   private:
      std::string version;
      std::string status;
};

}

std::ostream& operator<<(std::ostream&, const CouchDB::Revision&);

#endif
