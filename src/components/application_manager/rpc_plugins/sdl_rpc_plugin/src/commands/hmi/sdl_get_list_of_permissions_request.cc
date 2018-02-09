/*
 * Copyright (c) 2013, Ford Motor Company
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of the Ford Motor Company nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "sdl_rpc_plugin/commands/hmi/sdl_get_list_of_permissions_request.h"
#include "application_manager/application_manager.h"

namespace sdl_rpc_plugin {
using namespace application_manager;

namespace commands {

SDLGetListOfPermissionsRequest::SDLGetListOfPermissionsRequest(
    const application_manager::commands::MessageSharedPtr& message,
    ApplicationManager& application_manager)
    : RequestFromHMI(message, application_manager) {}

SDLGetListOfPermissionsRequest::~SDLGetListOfPermissionsRequest() {}

void SDLGetListOfPermissionsRequest::Run() {
  LOG4CXX_AUTO_TRACE(logger_);
  uint32_t connection_key = 0;
  if ((*message_)[strings::msg_params].keyExists(strings::app_id)) {
    connection_key = (*message_)[strings::msg_params][strings::app_id].asUInt();
  }
  application_manager_.GetPolicyHandler().OnGetListOfPermissions(
      connection_key,
      (*message_)[strings::params][strings::correlation_id].asUInt());
}

}  // namespace commands
}  // namespace application_manager