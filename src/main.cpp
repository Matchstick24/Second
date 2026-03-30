// Include //

#include "vke_main.h"

// Entry Point //

int main() 
{
    Vulkan_App vulkan_app;

    try 
    {
        vulkan_app.Run();
    } catch (const std::exception& except) 
    {
        std::cerr << except.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
