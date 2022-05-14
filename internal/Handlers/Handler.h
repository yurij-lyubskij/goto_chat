#ifndef GOTO_CHAT_HANDLER_H
#define GOTO_CHAT_HANDLER_H

#include "Request.h"
#include "Response.h"

class iHandler {
	public:
		virtual bool canHandle(Request) = 0;
		virtual Response handle(Request) = 0;
};

#endif