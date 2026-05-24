from conan import ConanFile

class Lesson0(ConanFile):
    name = "lesson0"
    version = "0.1"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("qt/6.8.3")

    def build_requirements(self):
        pass
