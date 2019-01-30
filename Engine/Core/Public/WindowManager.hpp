#ifndef DUSK_WINDOW_MANAGER_HPP
#define DUSK_WINDOW_MANAGER_HPP

#include <cstdint>
#include <string>

#include <Math.hpp>

namespace dusk {

using std::wstring;

typedef uint32_t WindowHandle;

class WindowManager
{
public:

    /** 
     * Disable Copy Constructor and Assignment Operator
     */
    WindowManager(const WindowManager&) = delete;
    WindowManager& operator=(const WindowManager&) = delete;

    /**
     * Return an instance to the current window manager.
     * 
     * @return The current window manager, or nullptr.
     */
    static WindowManager * Inst();

    /**
     * Open a new window, and return it's handle.
     * 
     * @param  title  The title for the new window.
     * @param  size   The size in pixels for the new window.
     * 
     * @return A handle to the new window.
     */
    virtual WindowHandle Open(const wstring& title, const ivec2& size) = 0;

    /**
     * Close a window.
     * 
     * @param  window  A handle to the window to close.
     */
    virtual bool Close(WindowHandle handle) = 0;

    /**
     * Poll for new events and dispatch event handlers.
     */
    virtual void PollEvents() = 0;

	/**
	* Swap the back and front buffers.
	*/
	virtual void SwapBuffers(WindowHandle handle) = 0;

    /**
     * Return the number of open windows.
     * 
     * @return The number of open windows.
     */
    virtual size_t Count() const = 0;

protected:

    WindowManager();

    virtual ~WindowManager();

    static WindowManager * s_Inst;

}; // class WindowManager

class NullWindowManager final : public WindowManager
{
public:

    NullWindowManager() = default;

    ~NullWindowManager() = default;

    WindowHandle Open(const wstring& title, const ivec2& size) override;

    bool Close(WindowHandle handle) override;

    void PollEvents() override;

	void SwapBuffers(WindowHandle handle) override;

    size_t Count() const override;

}; // class NullWindowManager

} // namespace dusk

#endif // DUSK_WINDOW_MANAGER_HPP
