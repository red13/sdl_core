/**
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

#ifndef SRC_COMPONENTS_AUDIO_MANAGER_INCLUDE_AUDIO_MANAGER_AUDIO_MANAGER_IMPL_H_
#define SRC_COMPONENTS_AUDIO_MANAGER_INCLUDE_AUDIO_MANAGER_AUDIO_MANAGER_IMPL_H_

#include <net/if.h>
#include <string>
#include <map>
#include "utils/logger.h"
#include "utils/macro.h"
#include "audio_manager/audio_manager.h"
#include "utils/threads/thread.h"
#include "utils/threads/thread_delegate.h"
#include "utils/synchronisation_primitives.h"

namespace audio_manager {

// TODO(PK): Introduce base class for SourcePlayerThread with different
// specific implementations if there are several different audio source
// types present.

class AudioManagerImpl : AudioManager {
 public:
  static AudioManager* getAudioManager();

  virtual void addA2DPSource(const sockaddr& device);
  virtual void removeA2DPSource(const sockaddr& device);
  virtual void playA2DPSource(const sockaddr& device);
  virtual void stopA2DPSource(const sockaddr& device);

  virtual void addA2DPSource(const string& device);
  virtual void removeA2DPSource(const string& device);
  virtual void playA2DPSource(const string& device);
  virtual void stopA2DPSource(const string& device);

  virtual ~AudioManagerImpl();

 protected:
  AudioManagerImpl();

  class A2DPSourcePlayerThread : public threads::ThreadDelegate {
   public:
    explicit A2DPSourcePlayerThread(const std::string& device);

    void threadMain();

    void exitThreadMain();

   private:
     // The Sample format to use
     static const pa_sample_spec sSampleFormat_;

     const int BUFSIZE_;
     pa_simple *s_in, *s_out;
     std::string device_;
     bool shouldBeStoped_;
     sync_primitives::SynchronisationPrimitives stopFlagMutex_;

     void freeStreams();

     DISALLOW_COPY_AND_ASSIGN(A2DPSourcePlayerThread);
    };


 private:
  std::map<std::string, threads::Thread*> sources_;

  const int MAC_ADDRESS_LENGTH_;
  static AudioManagerImpl* sInstance_;
  static log4cxx::LoggerPtr logger_;
  static const std::string sA2DPSourcePrefix_;

  std::string sockAddr2SourceAddr(const sockaddr& device);

  DISALLOW_COPY_AND_ASSIGN(AudioManagerImpl);
};

}  //  namespace audio_manager

#endif  // SRC_COMPONENTS_AUDIO_MANAGER_INCLUDE_AUDIO_MANAGER_AUDIO_MANAGER_IMPL_H_
