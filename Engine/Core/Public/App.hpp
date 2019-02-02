#ifndef DUSK_APP_HPP
#define DUSK_APP_HPP

#include "WindowManager.hpp"

#ifndef DUSK_VERSION_MAJOR
#define DUSK_VERSION_MAJOR 0
#endif

#ifndef DUSK_VERSION_MINOR
#define DUSK_VERSION_MINOR 0
#endif

#ifndef DUSK_VERSION_PATCH
#define DUSK_VERSION_PATCH 0
#endif

namespace dusk {

class App
{
public:

    /**
     * Disable Copy Constructor and Assignment Operator
     */
    App(const App&) = delete;
    App& operator=(const App&) = delete;

    /**
     * Return an instance to the current window manager.
     *
     * @return The current window manager, or nullptr.
     */
    static App * Inst();

    /**
     * Construct a default App instance.
     */
    App();
    virtual ~App();

    /**
     * Set the Application name.
     *
     * @param  name  The application name.
     */
    virtual void SetName(const char * name);

    /**
     * Set the Application version.
     *
     * @param  version  The application version, e.g. "1.2.3".
     */
    virtual void SetVersion(const char * version);

    /**
     * Initialize the Dusk Application.
     */
    virtual bool Init();

    /**
     * Terminate the Dusk Application, freeing all resources.
     */
    virtual void Term();

    /**
     * Get the Application name.
     *
     * @return The Application name.
     */
    virtual const char * GetName() const;
    /**
     * Get the Application version.
     *
     * @return The Application version.
     */
    virtual const char * GetVersion() const;

    /**
     * Get the Major portion of the Application version.
     *
     * @return The Major portion of the Application version.
     */
    virtual int GetVersionMajor() const;

    /**
     * Get the Minor portion of the Application version.
     *
     * @return The Minor portion of the Application version.
     */
    virtual int GetVersionMinor() const;

    /**
     * Get the Patch portion of the Application version.
     *
     * @return The Patch portion of the Application version.
     */
    virtual int GetVersionPatch() const;


private:

    static App * s_Inst;

    const char * _Name;

    const char * _Version;

    int _VersionMajor = 0,
        _VersionMinor = 0,
        _VersionPatch = 0;

    WindowManager * _WindowManager = nullptr;

}; // class App

} // namespace dusk

#endif // DUSK_APP_HPP