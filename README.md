# dynamic-meta-storms

![Version](https://img.shields.io/badge/Version-1.0%20for%20MetaPhlAn2-brightgreen)
![Release date](https://img.shields.io/badge/Release%20date-Jul.%2010%2C%202019-brightgreen.svg)



## Contents

- [Introduction](#introduction)
- [System Requirement and dependency](#system-requirement-and-dependency)
- [Installation guide](#installation-guide)
- [Supplementary](#supplementary)

# Introduction

Dynamic Meta-Storms can compare the identified species of metagenomes with phylogeny, meanwhile, dynamically locate the unclassified species to the virtual nodes of the phylogeny tree by their higher-level taxonomy information for comprehensive similarity measurement. The ultra-high speed and low memory consumption of this method also enables comparison of 100,000 metagenomes on a single computing node in ~7 hours.

# System Requirement and dependency

## Hardware Requirements

Dynamic Meta-Storms only requires a standard computer with sufficient RAM to support the operations defined by a user. For typical users, this would be a computer with about 2 GB of RAM. For optimal performance, we recommend a computer with the following specs:

  RAM: 8+ GB  
  CPU: 4+ cores, 3.3+ GHz/core

## Software Requirements

OpenMP library is the C/C++ parallel computing library. Most Linux releases have OpenMP already been installed in the system. In Mac OS X, to install the compiler that supports OpenMP, we recommend using the Homebrew package manager:
```
brew install gcc
```

# Installation guide

## Automatic Installation (recommended)

At present, Dynamic Meta-Storms provides a fully automatic installer for easy installation.

a. Download the package:
```
git clone https://github.com/qibebt-bioinfo/dynamic-meta-storms.git	
```

b. Install by installer:
```
cd dynamic-meta-storms
source install.sh
```

The package should take less than 1 minute to install on a computer with the specifications recommended above.

The example dataset could be found at “example” folder. Check the “example/Readme” for details about the demo run.

## Manual Installation

If the automatic installer fails, Dynamic Meta-Storms can still be installed manually.

a. Download the package:
```
git clone https://github.com/qibebt-bioinfo/dynamic-meta-storms.git	
```

b. Configure the environment variables (the default environment variable configuration file is “~/.bashrc”):
```
export Dynamic_MetaStorms=Path to Dynamic Meta-Storms
export PATH=”$PATH:$Dynamic_MetaStorms/bin/”
source ~/.bashrc
```
c. Compile the source code:
```
cd dynamic-meta-storms
make
```

# Supplementary

See “Readme.txt” in the package for usage and details.
