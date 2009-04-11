#include "../common/common.h"
#include "../common/framework.h"
using namespace std;

namespace{

struct Settings:
  public framework::settings::Base,
  public framework::settings::mixins::SocketTypeMixin,
  public framework::settings::mixins::AddressMixin,
  public framework::settings::mixins::PortMixin,
  public framework::settings::mixins::BufferSizeMixin {

  /*
   * NOTE: SocketTypeMixin is not mentioned in methods as we do not want this
   * option to be available in all modes (to be precise, in "select" mode).
   */

  /* override */ virtual std::string options() const{
    return
      framework::settings::mixins::AddressMixin::option() +
      framework::settings::mixins::PortMixin::option() +
      framework::settings::mixins::BufferSizeMixin::option();
  }

  /* override */ virtual std::string options_help() const{
    return string() +
      "-" + framework::settings::mixins::AddressMixin::letter()            + "\n"
        "  " + framework::settings::mixins::AddressMixin::description()    + "\n"
      "-" + framework::settings::mixins::PortMixin::letter()               + "\n"
        "  " + framework::settings::mixins::PortMixin::description()       + "\n"
      "-" + framework::settings::mixins::BufferSizeMixin::letter()         + "\n"
        "  " + framework::settings::mixins::BufferSizeMixin::description() + "\n";
  }

  /* override */ virtual int handle(char letter, char * optarg){
    int result;
    if (letter == framework::settings::mixins::AddressMixin::letter())
      result = framework::settings::mixins::AddressMixin::handle(optarg);
    else if (letter == framework::settings::mixins::PortMixin::letter())
      result = framework::settings::mixins::PortMixin::handle(optarg);
    else if (letter == framework::settings::mixins::BufferSizeMixin::letter())
      result = framework::settings::mixins::BufferSizeMixin::handle(optarg);
    else
      return 1;

    switch(result){
      case 0:
        return 0;
      case 1:
        return 2;
      case 2:
        return 3;
      default:
        assert(false);
        return 3;
    }
  }

  /* override */ virtual bool validate(){
    bool success = true;
    if (!framework::settings::mixins::AddressMixin::is_set()){
      success = false;
      cerr << "ERROR: Option '-" << framework::settings::mixins::AddressMixin::letter() << "' is required.\n";
    }
    if (!framework::settings::mixins::PortMixin::is_set()){
      success = false;
      cerr << "ERROR: Option '-" << framework::settings::mixins::PortMixin::letter() << "' is required.\n";
    }
    if (!framework::settings::mixins::BufferSizeMixin::is_set()){
      success = false;
      cerr << "ERROR: Option '-" << framework::settings::mixins::BufferSizeMixin::letter() << "' is required.\n";
    }
    return success;
  }
};

struct CxxIoSettings:
  public Settings,
  public framework::settings::mixins::CxxIoInputMixin,
  public framework::settings::mixins::CxxIoOutputMixin {

  /* override */ virtual std::string options() const{
    return Settings::options()
      + framework::settings::mixins::CxxIoInputMixin::option()
      + framework::settings::mixins::CxxIoOutputMixin::option();
  }

  /* override */ virtual std::string options_help() const{
    return string() +
      "-" + framework::settings::mixins::CxxIoInputMixin::letter()          + "\n"
        "  " + framework::settings::mixins::CxxIoInputMixin::description()  + "\n"
      "-" + framework::settings::mixins::CxxIoOutputMixin::letter()         + "\n"
        "  " + framework::settings::mixins::CxxIoOutputMixin::description() + "\n"
      + Settings::options_help();
  }

  /* override */ virtual int handle(char letter, char * optarg){
    int result = Settings::handle(letter, optarg);
    if (result == 1){
      if (letter == framework::settings::mixins::CxxIoInputMixin::letter())
        result = framework::settings::mixins::CxxIoInputMixin::handle(optarg);
      else if (letter == framework::settings::mixins::CxxIoOutputMixin::letter())
        result = framework::settings::mixins::CxxIoOutputMixin::handle(optarg);
    }
    switch(result){
      case 0:
        return 0;
      case 1:
        return 2;
      case 2:
        return 3;
      default:
        assert(false);
        return 3;
    }
  }

  /* override */ virtual bool validate(){
    bool success = true;
    if (!framework::settings::mixins::CxxIoInputMixin::is_set()){
      success = false;
      cerr << "ERROR: Option '-" << framework::settings::mixins::CxxIoInputMixin::letter() << "' is required.\n";
    }
    if (!framework::settings::mixins::CxxIoOutputMixin::is_set()){
      success = false;
      cerr << "ERROR: Option '-" << framework::settings::mixins::CxxIoOutputMixin::letter() << "' is required.\n";
    }
      /*
       * Careful, Settings::validate() must fire even if success is already false.
       */
    success = Settings::validate() && success;
    return success;
  }
};

struct CIoSettings:
  public Settings,
  public framework::settings::mixins::CIoInputMixin,
  public framework::settings::mixins::CIoOutputMixin {

  /* override */ virtual std::string options() const{
    return Settings::options()
      + framework::settings::mixins::CIoInputMixin::option()
      + framework::settings::mixins::CIoOutputMixin::option();
  }

  /* override */ virtual std::string options_help() const{
    return string() +
      "-" + framework::settings::mixins::CIoInputMixin::letter()          + "\n"
        "  " + framework::settings::mixins::CIoInputMixin::description()  + "\n"
      "-" + framework::settings::mixins::CIoOutputMixin::letter()         + "\n"
        "  " + framework::settings::mixins::CIoOutputMixin::description() + "\n"
      + Settings::options_help();
  }

  /* override */ virtual int handle(char letter, char * optarg){
    int result = Settings::handle(letter, optarg);
    if (result == 1){
      if (letter == framework::settings::mixins::CIoInputMixin::letter())
        result = framework::settings::mixins::CIoInputMixin::handle(optarg);
      else if (letter == framework::settings::mixins::CIoOutputMixin::letter())
        result = framework::settings::mixins::CIoOutputMixin::handle(optarg);
    }
    switch(result){
      case 0:
        return 0;
      case 1:
        return 2;
      case 2:
        return 3;
      default:
        assert(false);
        return 3;
    }
  }

  /* override */ virtual bool validate(){
    bool success = true;
    if (!framework::settings::mixins::CIoInputMixin::is_set()){
      success = false;
      cerr << "ERROR: Option '-" << framework::settings::mixins::CIoInputMixin::letter() << "' is required.\n";
    }
    if (!framework::settings::mixins::CIoOutputMixin::is_set()){
      success = false;
      cerr << "ERROR: Option '-" << framework::settings::mixins::CIoOutputMixin::letter() << "' is required.\n";
    }
      /*
       * Careful, Settings::validate() must fire even if success is already false.
       */
    success = Settings::validate() && success;
    return success;
  }
};

typedef CxxIoSettings SelectWindowsSettings;
typedef CIoSettings SelectUnixSettings;

struct SimpleSettings: public CxxIoSettings{

  /* override */ virtual std::string options() const{
    return CxxIoSettings::options() +
      framework::settings::mixins::SocketTypeMixin::option();
  }

  /* override */ virtual std::string options_help() const{
    return string() +
      "-" + framework::settings::mixins::SocketTypeMixin::letter()         + "\n"
        "  " + framework::settings::mixins::SocketTypeMixin::description() + "\n"
      + CxxIoSettings::options_help();
  }

  /* override */ virtual int handle(char letter, char * optarg){
    int result = CxxIoSettings::handle(letter, optarg);
    if (result == 1){
      if (letter == framework::settings::mixins::SocketTypeMixin::letter())
        result = framework::settings::mixins::SocketTypeMixin::handle(optarg);
    }
    switch(result){
      case 0:
        return 0;
      case 1:
        return 2;
      case 2:
        return 3;
      default:
        assert(false);
        return 3;
    }
  }

  /* override */ virtual bool validate(){
    bool success = true;
    if (!framework::settings::mixins::SocketTypeMixin::is_set()){
      success = false;
      cerr << "ERROR: Option '-" << framework::settings::mixins::SocketTypeMixin::letter() << "' is required.\n";
    }
      /*
       * Careful, Settings::validate() must fire even if success is already false.
       */
    success = CxxIoSettings::validate() && success;
    return success;
  }
};

typedef vector<__int8_t> Buffer;
typedef bool (*Handler)(Settings * settings, int s);
typedef framework::Framework<Handler> ThisFramework;

bool invoke_handler(Handler handler, framework::settings::Base * settings_){
  Settings * settings = static_cast<Settings *>(settings_);
  bool ret = false;

  #ifdef WIN32
    WSADATA wsadata;
    if (WSAStartup(MAKEWORD(2, 2), &wsadata)){
      cerr << "ERROR: Could not initialize socket library\n";
      return false;
    }
  #endif

  addrinfo * res = 0;
  addrinfo * p = 0;
  int s = -1; // Our socket

  addrinfo hints = {0};
  hints.ai_family = AF_UNSPEC; // AF_INET or AF_INET6 to force version
  hints.ai_socktype = settings->socket_type;
  if (getaddrinfo(
        settings->addr.c_str(),
        settings->port.c_str(),
        &hints, &res) != 0){
    cerr << "ERROR: Could not resolve IP address and/or port\n";
    goto run_return;
  }

  for(p = res; p != NULL; p = p->ai_next){
    s = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (s == -1)
      continue;
    if (connect(s, p->ai_addr, p->ai_addrlen) == -1){
      verify_ne(close(s), -1);
      s = -1;
      continue;
    }
    break;
  }
  if (s == -1){
    cerr << "ERROR: Could not connect to server\n";
    goto run_return;
  }

  ret = handler(settings, s);
run_return:
  if (res != 0)
    freeaddrinfo(res);
  if (s != -1)
    verify_ne(close(s), -1);
  return ret;
}

bool simple_handler(Settings * settings_, int s){
  SimpleSettings * settings = static_cast<SimpleSettings *>(settings_);

  istream & input = settings->get_input();
  ostream & output = settings->get_output();

  Buffer buffer(settings->buffer_size);
  __int8_t * const buf = &buffer[0];

  while (!input.eof()){

    input.read(reinterpret_cast<char *>(buf), settings->buffer_size / sizeof(char));
    int count = input.gcount() * sizeof(char);
    if (count == 0)
      continue;
    cerr << "TRACE: " << count << " bytes to send\n";

    int sent_total = 0;
    while (sent_total < count){
      int sent_current = send(s, buf + sent_total, count - sent_total, 0);
      if (sent_current == -1){
        cerr << "ERROR: Encountered an error while sending data\n";
        return false;
      }
      cerr << "TRACE: " << sent_current << " bytes sent\n";
      sent_total += sent_current;
    }
    cerr << "TRACE: Start receiving\n";

    int recv_total = 0;
    while (recv_total < count){
      int recv_current = recv(s, buf + recv_total, settings->buffer_size - recv_total, 0);
      if (recv_current == -1){
        cerr << "ERROR: Encountered an error while reading data\n";
        return false;
      }
      if (recv_current == 0){
        cerr << "ERROR: Server shutdowned unexpectedly\n";
        return false;
      }
      cerr << "TRACE: Received " << recv_current << " bytes\n";
      recv_total += recv_current;
    }
    output.write(reinterpret_cast<char *>(buf), recv_total * sizeof(char));
  }
  return true;
}

bool select_windows_handler(Settings * settings_, int s){
  SelectWindowsSettings * settings = static_cast<SelectWindowsSettings *>(settings_);

  istream & input = settings->get_input();
  ostream & output = settings->get_output();

  Buffer buffer(settings->buffer_size);
  __int8_t * const buf = &buffer[0];

  bool stdin_eof = false;

  fd_set rset, wset;
  FD_ZERO(&rset);
  FD_ZERO(&wset);

  for (;;){
    FD_SET(s, &rset);
    if (!stdin_eof)
      FD_SET(s, &wset);

    cerr << "TRACE: calling select()\n";
    int num_ready = select(s + 1, &rset, &wset, 0, 0);
    if (num_ready == -1){
      cerr << "ERROR: select() reported an error\n";
      return false;
    }

    if (FD_ISSET(s, &rset)){
      int received = recv(s, buf, settings->buffer_size, 0);
      if (received == -1){
        SOCKETS_PERROR("ERROR: Error when receiving");
        return false;
      }
      else if (received == 0){
        if (stdin_eof){
          cerr << "TRACE: Server closed the connection\n";
          return true;
        }
        else{
          cerr << "ERROR: Server closed the connection unexpectedly\n";
          return false;
        }
      }
      else {
        cerr << "TRACE: " << received << " bytes to print\n";
        output.write(reinterpret_cast<char *>(buf), received * sizeof(char));
        cerr << "TRACE: Bytes printed\n";
      }
    }

    if (FD_ISSET(s, &wset)){
      input.read(reinterpret_cast<char *>(buf), settings->buffer_size / sizeof(char));
      int count = input.gcount() * sizeof(char);
      if (count == 0){
        cerr << "TRACE: EOF at standard input\n";
        stdin_eof = true;
        verify_ne(shutdown(s, SHUT_WR), -1);
        FD_CLR(s, &wset);
      }
      else{
        cerr << "TRACE: " << count << " bytes to send\n";

        int sent = send(s, buf, count, 0);
        if (sent == -1){
          SOCKETS_PERROR("ERROR: Error when sending");
          return false;
        }
        else{
          assert(sent == count);
          cerr << "TRACE: " << sent << " bytes sent\n";
        }
      }
    }
  }
}

#ifdef UNIX
  /*
   * In Unix we can pass to select() file descriptors.
   */
bool select_unix_handler(Settings * settings_, int s){
  SelectUnixSettings * settings = static_cast<SelectUnixSettings *>(settings_);

  int input = fileno(settings->get_input());
  int output = fileno(settings->get_output());

  ReadWriteBuffer to(settings->buffer_size);
  ReadWriteBuffer from(settings->buffer_size);

  enum{
    STATE_NORMAL,
    STATE_NO_INPUT,
    STATE_ALL_SENT,
  } state = STATE_NORMAL;

  for (;;){

    fd_set rset, wset;
    FD_ZERO(&rset);
    FD_ZERO(&wset);
    int maxfd = 0;

    if (!to.rd_empty()){
      FD_SET(s, &rset);
      maxfd = max(maxfd, s);
    }
    if (!to.snd_empty()){
      FD_SET(output, &wset);
      maxfd = max(maxfd, output);
    }

    if (state < STATE_NO_INPUT && !from.rd_empty()){
      FD_SET(input, &rset);
      maxfd = max(maxfd, input);
    }
    if (state < STATE_ALL_SENT && !from.snd_empty()){
      FD_SET(s, &wset);
      maxfd = max(maxfd, s);
    }

    int num_ready = select(maxfd + 1, &rset, &wset, 0, 0);
    if (num_ready == -1){
      cerr << "ERROR: select() reported an error\n";
      return false;
    }

      /*
       * Check this BEFORE FD_ISSET(s, &rset) in order not to return too early.
       */
    if (FD_ISSET(output, &wset)){
      int count = write(output, &*(to.snd_begin()), to.snd_size());
      if (count == -1){
        cerr << "ERROR: An error occured while writing to output.\n";
        return false;
      }
      else
        to.snd_advance(count);
    }

    if (FD_ISSET(s, &rset)){
      int count = recv(s, &*(to.rd_begin()), to.rd_size(), 0);
      if (count == -1){
        SOCKETS_PERROR("ERROR: Error when receiving");
        return false;
      }
      else if (count == 0){
        if (state == STATE_ALL_SENT){
          cerr << "TRACE: Server closed the connection.\n";
          return true;
        }
        else{
          cerr << "ERROR: Server closed the connection unexpectedly.\n";
          return false;
        }
      }
      else
        to.rd_advance(count);
    }

    if (FD_ISSET(input, &rset)){
      int count = read(input, &*(from.rd_begin()), from.rd_size());
      if (count == -1){
        cerr << "ERROR: An error occured while reading from input.\n";
        return false;
      }
      else if (count == 0){
        cerr << "TRACE: EOF at standard input.\n";
        state = STATE_NO_INPUT;

        if (from.snd_empty()){
          verify_ne(shutdown(s, SHUT_WR), -1);
          state = STATE_ALL_SENT;
        }
      }
      else
        from.rd_advance(count);
    }

    if (FD_ISSET(s, &wset)){
      int count = send(s, &*(from.snd_begin()), from.snd_size(), 0 /* flags */);
      if (count == -1){
        SOCKETS_PERROR("ERROR: Error while sending.");
        return false;
      }
      else{
        from.snd_advance(count);
        if (state == STATE_NO_INPUT && from.snd_empty()){
          verify_ne(shutdown(s, SHUT_WR), -1);
          state = STATE_ALL_SENT;
        }
      }
    }
  }
}
#endif

} // namespace

int main(int argc, char ** argv){
  SimpleSettings        simple_settings;
  SelectWindowsSettings select_windows_settings;
  SelectUnixSettings    select_unix_settings;

  vector<string> select_windows_mode_names;
  #ifdef WIN32
    select_windows_mode_names.push_back("select");
  #endif
  select_windows_mode_names.push_back("select-windows");

  ThisFramework::Modes modes;
  modes.push_back(ThisFramework::ModeDescription(
    "simple",
    "Simple client.",
    &simple_settings,
    &simple_handler));
  modes.push_back(ThisFramework::ModeDescription(
    select_windows_mode_names,
    "Client implemented using select() function.",
    &select_windows_settings,
    &select_windows_handler));
  #ifdef UNIX
    modes.push_back(ThisFramework::ModeDescription(
      "select",
      "Client implemented using select() with Unix-specific optimizations.",
      &select_unix_settings,
      &select_unix_handler));
  #endif
  return ThisFramework::run("client", argc, argv, modes, invoke_handler) ? 0 : 1;
}
