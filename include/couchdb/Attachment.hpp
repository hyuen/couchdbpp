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
#ifndef __COUCH_DB_ATTACHMENT_HPP__
#define __COUCH_DB_ATTACHMENT_HPP__

#include <string>
#include <iostream>

#include "couchdb/Communication.hpp"

namespace CouchDB{

class Attachment{
   friend class Document;

   protected:
      Attachment(Communication&, const std::string&, const std::string&,
                 const std::string&, const std::string&, const std::string&);

   public:
      Attachment(const Attachment&);
      ~Attachment();

      Attachment& operator=(Attachment&);

      const std::string& getID() const;
      const std::string& getRevision() const;
      const std::string& getContentType() const;

      std::string getData();

   private:
      Communication &comm;
      std::string   db;
      std::string   document;
      std::string   id;
      std::string   revision;
      std::string   contentType;
      std::string   rawData;
};

}

std::ostream& operator<<(std::ostream&, const CouchDB::Attachment&);

#endif
