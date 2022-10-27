#include <leveldb/db.h>
#include <glog/logging.h>
#include <leveldb/iterator.h>
#include <leveldb/options.h>


int main() {
  leveldb::DB* db = nullptr;
  leveldb::Options option;
  option.create_if_missing = true;
  leveldb::Status status = leveldb::DB::Open(option, "/tmp/test_db", &db);
  assert(nullptr != db);
  if (!status.ok()) {
    LOG(ERROR) << "db init error " << status.ToString();
  }
  std::string key = "123";
  std::string value = "456";
  status = db->Put(leveldb::WriteOptions(), key, value);
  std::string key_1 = "1323";
  status = db->Put(leveldb::WriteOptions(), key_1, value);
  if (!status.ok()) {
    LOG(ERROR) << "db put error " << status.ToString();
  }
  leveldb::Iterator* iter = db->NewIterator(leveldb::ReadOptions());
  for (iter->SeekToFirst(); iter->Valid(); iter->Next()) {
    LOG(INFO) << iter->key().ToString() << ": " << iter->value().ToString();
  }
  delete db;
  return 0;
}