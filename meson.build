project(
    'cppversus-cli',
    'cpp',
    version : '1.0',
    default_options : [
        'cpp_std=c++20',
        'warning_level=2'
    ]
)

executable(
    'cli',
    sources: [
        'src/main.cpp'
    ],
    include_directories: [
        include_directories('include')
    ],
    dependencies: [
        dependency('cppversus'),
        dependency('cli11'),
        dependency('spdlog')
    ]
)