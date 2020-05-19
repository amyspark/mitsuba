*DISCLAIMER: This is a **fork** of [the original repository](https://github.com/mitsuba-renderer/mitsuba). Report issues, pull requests, etc. by following the badges below. Thanks!*

Mitsuba — Physically Based Renderer [![][issues]][issues-link] [![][pulls]][pulls-link] [![][stars]][stars-link] [![][license]][license-link] [![][travis]][travis-link] [![][appveyor]][appveyor-link]
===================================

http://mitsuba-renderer.org/

## About

Mitsuba is a research-oriented rendering system in the style of PBRT, from which it derives much inspiration. It is written in portable C++, implements unbiased as well as biased techniques, and contains heavy optimizations targeted towards current CPU architectures. Mitsuba is extremely modular: it consists of a small set of core libraries and over 100 different plugins that implement functionality ranging from materials and light sources to complete rendering algorithms.

In comparison to other open source renderers, Mitsuba places a strong emphasis on experimental rendering techniques, such as path-based formulations of Metropolis Light Transport and volumetric modeling approaches. Thus, it may be of genuine interest to those who would like to experiment with such techniques that haven't yet found their way into mainstream renderers, and it also provides a solid foundation for research in this domain.

The renderer currently runs on Linux, MacOS X and Microsoft Windows and makes use of SSE2 optimizations on x86 and x86_64 platforms. So far, its main use has been as a testbed for algorithm development in computer graphics, but there are many other interesting applications.

Mitsuba comes with a command-line interface as well as a graphical frontend to interactively explore scenes. While navigating, a rough preview is shown that becomes increasingly accurate as soon as all movements are stopped. Once a viewpoint has been chosen, a wide range of rendering techniques can be used to generate images, and their parameters can be tuned from within the program.

## Documentation

For compilation, usage, and a full plugin reference, please see the [official documentation](http://mitsuba-renderer.org/docs.html).

## Releases and scenes

Pre-built binaries, as well as example scenes, are available on the [Mitsuba website](http://mitsuba-renderer.org/download.html).

[issues]: https://img.shields.io/github/issues/mitsuba-renderer/mitsuba.svg (GitHub issues)
[issues-link]: https://github.com/mitsuba-renderer/mitsuba/issues
[pulls]: https://img.shields.io/github/issues-pr/mitsuba-renderer/mitsuba.svg (GitHub pull requests)
[pulls-link]: https://github.com/mitsuba-renderer/mitsuba/pulls
[stars]: https://img.shields.io/github/stars/mitsuba-renderer/mitsuba.svg (GitHub stars)
[stars-link]: https://github.com/mitsuba-renderer/mitsuba/stargazers
[license]: https://img.shields.io/badge/license-GPL3-blue.svg (License: GPLv3)
[license-link]: ./LICENSE
[travis]: https://img.shields.io/travis/amyspark/mitsuba.svg (Travis-CI status)
[travis-link]: https://travis-ci.org/amyspark/mitsuba
[appveyor]: https://ci.appveyor.com/api/projects/status/8v8u6lnc8krqxkuu?svg=true (Appveyor status)
[appveyor-link]: https://ci.appveyor.com/project/amyspark/mitsuba
