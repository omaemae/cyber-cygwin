cmake_minimum_required(VERSION 3.5)
project(cyber-icon-theme)

include(FeatureSummary)

install(DIRECTORY Crule DESTINATION /usr/share/icons)
install(DIRECTORY Crule-dark DESTINATION /usr/share/icons)
