#pragma once

#include <sw/redis++/redis++.h>
#include <iostream>
#include <vector>

#include <phpcpp.h>

namespace RedisDb {

    void flushall() {
        auto redis = sw::redis::Redis("tcp://127.0.0.1:6379/0");
        redis.flushall();
    }
    
    class set : public Php::Base {
        public: void static push_array(std::string index_name, std::vector<std::string> value) {
            auto redis = sw::redis::Redis("tcp://127.0.0.1:6379/0");
            redis.rpush(index_name, value.begin(), value.end());
        }

        public: void static push_array_field(std::string array_field, std::string index_name, std::string value) {
            auto redis = sw::redis::Redis("tcp://127.0.0.1:6379/0");
            redis.hset(array_field, std::make_pair(index_name, value));
        }

        public: void static string(std::string index_name, std::string value) {
            auto redis = sw::redis::Redis("tcp://127.0.0.1:6379/0");
            redis.set(index_name, value);
        }

    };

    class get : public Php::Base {
        public: std::vector<std::string> static array(std::string index_name) {
            auto redis = sw::redis::Redis("tcp://127.0.0.1:6379/0");
            std::vector<std::string> value;
            // redis.lrange(index_name, 0, -1, std::back_inserter(value));
            return {"test"};
        }

        public: std::unordered_map<std::string, std::string> static array_field(std::string index_name) {
            auto redis = sw::redis::Redis("tcp://127.0.0.1:6379/0");
            std::unordered_map<std::string, std::string> value;
            redis.hgetall(index_name, std::inserter(value, value.begin()));
            return value;
        }

        public: std::string static string(std::string index_name) {
            auto redis = sw::redis::Redis("tcp://127.0.0.1:6379/0");
            auto value = redis.get(index_name);
            return *value;
        }

    };
}

