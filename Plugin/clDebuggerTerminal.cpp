#include "clDebuggerTerminal.h"
#include "globals.h"
#include "file_logger.h"

#ifndef __WXMSW__
#   include <sys/wait.h>
#endif

clDebuggerTerminalPOSIX::clDebuggerTerminalPOSIX()
    : m_pid(wxNOT_FOUND)
{
}

clDebuggerTerminalPOSIX::~clDebuggerTerminalPOSIX()
{
}

void clDebuggerTerminalPOSIX::Launch(const wxString &title)
{
    m_title = title;
    ::LaunchTerminalForDebugger(m_title, m_tty, m_pid);
    if ( IsValid() ) {
        CL_DEBUG("clDebuggerTerminalPOSIX successfully started. Process %d", (int)m_pid);
    }
}

bool clDebuggerTerminalPOSIX::IsValid() const
{
    return m_pid != wxNOT_FOUND && !m_tty.IsEmpty();
}

void clDebuggerTerminalPOSIX::Clear()
{
#ifndef __WXMSW__
    if ( m_pid != wxNOT_FOUND ) {
        // terminate the process
        ::wxKill(m_pid, wxSIGKILL);
    }
#endif
    m_pid = wxNOT_FOUND;
    m_tty.Clear();
    m_title.Clear();
    
//#ifndef __WXMSW__
//    int status = 0;
//    int pid(0);
//    do {
//       pid = ::waitpid(-1, &status, WNOHANG); 
//       if ( pid > 0 ) {
//           CL_DEBUG("clDebuggerTerminalPOSIX Process %d exited with status code %d", pid, WEXITSTATUS(status));
//           wxThread::Sleep(50);
//       }
//    } while( pid ); 
//#endif
}