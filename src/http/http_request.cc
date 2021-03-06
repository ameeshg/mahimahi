/* -*-mode:c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

#include <sstream>
#include <vector>

#include "exception.hh"
#include "ezio.hh"
#include "http_request.hh"

using namespace std;

void HTTPRequest::calculate_expected_body_size(void) {
  assert(state_ == BODY_PENDING);

  if (first_line_.substr(0, 4) == "GET " or
      first_line_.substr(0, 5) == "HEAD ") {
    set_expected_body_size(true, 0);
  } else if (first_line_.substr(0, 5) == "POST ") {
    if (!has_header("Content-Length")) {
      throw runtime_error("HTTPRequest: does not support chunked requests");
    }

    set_expected_body_size(true, myatoi(get_header_value("Content-Length")));
  } else {
    throw runtime_error("Cannot handle HTTP method: " + first_line_);
  }
}

size_t HTTPRequest::read_in_complex_body(const std::string &) {
  /* we don't support complex bodies */
  throw runtime_error("HTTPRequest: does not support chunked requests");
}

bool HTTPRequest::eof_in_body(void) const {
  throw runtime_error("HTTPRequest: got EOF in middle of body");
}

bool HTTPRequest::is_head(void) const {
  assert(state_ > FIRST_LINE_PENDING);
  /* RFC 2616 5.1.1 says "The method is case-sensitive." */
  return first_line_.substr(0, 5) == "HEAD ";
}

string HTTPRequest::get_url(void) const {
  string host = "";
  for (auto it = headers_.begin(); it != headers_.end(); it++) {
    auto header = *it;
    auto key = header.key();
    auto value = header.value();
    if (key == "Host") {
      host = value;
      break;
    }
  }

  // Cannot find the host of this request.
  if (host.empty()) {
    return "";
  }

  stringstream ss(first_line_);
  string item;
  vector<string> tokens;
  while (getline(ss, item, ' ')) {
    tokens.push_back(item);
  }
  return host + tokens[1];
}
