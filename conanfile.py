from conan import ConanFile
from conan.tools.cmake import CMake


class CustomWidgetConan(ConanFile):
    name = "custom_widget"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"
    requires = "nlohmann_json/3.11.2"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
