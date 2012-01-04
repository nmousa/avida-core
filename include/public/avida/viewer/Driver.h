/*
 *  viewer/Driver.h
 *  avida-core
 *
 *  Created by David on 10/28/10.
 *  Copyright 2010-2011 Michigan State University. All rights reserved.
 *  http://avida.devosoft.org/
 *
 *
 *  This file is part of Avida.
 *
 *  Avida is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 *
 *  Avida is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License along with Avida.
 *  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Authors: David M. Bryson <david@programerror.com>
 *
 */

#ifndef AvidaViewerDriver_h
#define AvidaViewerDriver_h

#include "apto/core.h"
#include "avida/core/Feedback.h"
#include "avida/core/WorldDriver.h"
#include "avida/data/Recorder.h"

class cWorld;


namespace Avida {
  namespace Viewer {

    // Class Declarations
    // --------------------------------------------------------------------------------------------------------------  
    
    class Map;
    class Listener;


    // Enumerations
    // --------------------------------------------------------------------------------------------------------------  
    
    enum DriverPauseState {
      DRIVER_PAUSED,
      DRIVER_UNPAUSED
    };

    
    // Driver Definition
    // --------------------------------------------------------------------------------------------------------------  
    
    class Driver : public Apto::Thread, public Avida::WorldDriver
    {
    private:
      cWorld* m_world;
      World* m_new_world;
      
      Apto::Mutex m_mutex;
      Apto::ConditionVariable m_pause_cv;
      DriverPauseState m_pause_state;
      bool m_done;
      bool m_paused;
      
      Avida::DriverCallback m_callback;
      
      Map* m_map;
      
      Apto::Set<Listener*> m_listeners;

      class StdIOFeedback : public Avida::Feedback
      {
        void Error(const char* fmt, ...);
        void Warning(const char* fmt, ...);
        void Notify(const char* fmt, ...);
      } m_feedback;

      
    public:
      LIB_EXPORT Driver(cWorld* world, World* new_world);
      LIB_EXPORT ~Driver();
      
      LIB_EXPORT static Driver* InitWithDirectory(const Apto::String& dir);
      
      LIB_EXPORT inline World* GetWorld() { return m_new_world; }
      
      LIB_EXPORT DriverPauseState GetPauseState() const { return m_pause_state; }
      LIB_EXPORT bool IsPaused() const { return m_paused; }
      LIB_EXPORT void Resume();
      
      LIB_EXPORT void AttachListener(Listener* listener);
      LIB_EXPORT void DetachListener(Listener* listener) { m_listeners.Remove(listener); }

      LIB_EXPORT void AttachRecorder(Data::RecorderPtr recorder);
      LIB_EXPORT void DetachRecorder(Data::RecorderPtr recorder);

      
      // WorldDriver Protocol
      // ------------------------------------------------------------------------------------------------------------  
      
    public:
      // Actions
      LIB_EXPORT void Pause();
      LIB_EXPORT void Finish();
      LIB_EXPORT void Abort(AbortCondition condition);
      
      // Facilities
      LIB_EXPORT Avida::Feedback& Feedback() { return m_feedback; }

      // Callback methods
      LIB_EXPORT void RegisterCallback(DriverCallback callback);
      
      
      // Apto::Thread Interface
      // ------------------------------------------------------------------------------------------------------------  
      
    protected:
      LIB_LOCAL void Run();
    };

  };
};

#endif