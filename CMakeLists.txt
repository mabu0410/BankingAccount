cmake_minimum_required(VERSION 3.10)
project(BankingSystem VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/Menu.cpp
    src/models/User.cpp
    src/models/Account.cpp
    src/models/Transaction.cpp
    src/services/UserService.cpp
    src/services/AccountService.cpp
    src/services/TransactionService.cpp
    src/controllers/AuthController.cpp
    src/controllers/AccountController.cpp
    src/controllers/TransactionController.cpp
    src/utils/FileHandler.cpp
    src/utils/Validator.cpp
    src/utils/Helper.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)
