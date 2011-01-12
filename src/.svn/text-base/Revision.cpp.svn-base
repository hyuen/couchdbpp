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
#include "couchdb/Revision.hpp"

using namespace std;
using namespace CouchDB;

Revision::Revision(const string &_version, const string &_status)
   : version(_version)
   , status(_status)
{
}

Revision::Revision(const Revision &revision)
   : version(revision.getVersion())
   , status(revision.getStatus())
{
}

Revision::~Revision(){
}

const string& Revision::getVersion() const{
   return version;
}

const string& Revision::getStatus() const{
   return status;
}

ostream& operator<<(ostream &out, const CouchDB::Revision &rev){
   return out << "{rev: " << rev.getVersion() << ", status: " << rev.getStatus() << "}";
}
