# BALLS

[![Join the chat at https://gitter.im/JesseTG/BALLS](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/JesseTG/BALLS?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
Badass Looker for Ludicrous Shaders

[![Build Status](https://travis-ci.org/JesseTG/BALLS.svg?branch=master)](https://travis-ci.org/JesseTG/BALLS)

## Compiling

BALLS uses submodules, so clone it with:

    git clone --recursive

When you do, run `qmake` from the root of the repository (or just open up the `.pro` in Qt Creator):

    qmake ./BALLS/BALLS.pro

Finally, just run the resulting `Makefile`:

    make

If the build is any more complex than that, please, *please* [file an issue](https://github.com/JesseTG/BALLS/issues).  Nothing pisses me off more than software that's a pain to install.

### Build options

You can customize the build by adding flags on the command line like so:

    qmake ./BALLS/BALLS.pro SOMEVAR+=somevalue

No such supported configurations exist right now, but they will.
