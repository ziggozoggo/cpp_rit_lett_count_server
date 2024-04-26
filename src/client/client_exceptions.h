#ifndef SRC_CLIENT_EXCEPTIONS_H_
#define SRC_CLIENT_EXCEPTIONS_H_

#include <exception>
#include <string>

class ClientConnectToServerFailed : public std::exception {
 public:
  ClientConnectToServerFailed(const std::string &message) : message_(message){};
  const char *what() const noexcept override { return message_.c_str(); }

 private:
  std::string message_;
};

class ClientCreateSocketFailed : public std::exception {
 public:
  ClientCreateSocketFailed(const std::string &message) : message_(message){};
  const char *what() const noexcept override { return message_.c_str(); }

 private:
  std::string message_;
};

class ClientServerConnectionLost : public std::exception {
 public:
  ClientServerConnectionLost(const std::string &message) : message_(message){};
  const char *what() const noexcept override { return message_.c_str(); }

 private:
  std::string message_;
};

#endif  // SRC_CLIENT_EXCEPTIONS_H_