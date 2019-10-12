# Dynamic Meta-Storms

![Version](https://img.shields.io/badge/Version-1.0%20for%20MetaPhlAn2-brightgreen)
![Release date](https://img.shields.io/badge/Release%20date-Jul.%2010%2C%202019-brightgreen.svg)



## Contents

- [Introduction](#introduction)
- [System Requirement and dependency](#system-requirement-and-dependency)
- [Installation guide](#installation-guide)
- [Usage](#usage)
- [Example dataset](#example-dataset)
- [Tools in this package](#tools-in-this-package)
- [Supplementary](#supplementary)

# Introduction

Dynamic Meta-Storms calculates comprehensive taxonomic and phylogenetic distances/dissimilarities of shotgun metagenomes at the species level. It takes the species-level profiling results of MetaPhlAn2 as input, and compares metagenomes on the species-level with both taxonomy and phylogeny profiles. When comparing samples, for organisms that can be identified by species, Dynamic Meta-Storms measures their dissimilarity based on the species-level phylogeny tree using the Meta-Storms algorithm; for unclassified species, it dynamically locates such organisms to the virtual internal nodes that account for all the sub-branches under the same taxonomy.

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
export DynamicMetaStorms=Path to Dynamic Meta-Storms
export PATH=”$PATH:$DynamicMetaStorms/bin/”
source ~/.bashrc
```
c. Compile the source code:
```
cd dynamic-meta-storms
make
```
# Usage
a. Metagenomic species-level profiling by MetaPhlAn2

Dynamic Meta-Storms takes the species-level profiling results of MetaPhlAn2 as input. You can either start from the metagenomics sequence file:
```
metaphlan2.py sample_1.fasta --input_type fasta --tax_lev s --ignore_viruses --ignore_eukaryotes --ignore_archaea > profiled_sample_1.sp.txt
```
or you can start from the intermediate BowTie2 output by MetaPhlAn2:
```
metaphlan2.py sample_1.bowtie2.bz2 --input_type bowtie2out --tax_lev s --ignore_viruses --ignore_eukaryotes --ignore_archaea > profiled_sample_1.sp.txt
```
This step can be ignored if you have already obtained the species-level relative abundance table by MetaPhlAn2 (e.g. [Example dataset](#example-dataset) in below).

b. Merge multiple output files to species-level relative abundance table

To merge output files of multiple samples, please summarize all samples’ output information into a list file (e.g. named as samples.list.txt) in the following format:
```
Sample_1	profiled_sample_1.sp.txt
Sample_2	profiled_sample_2.sp.txt
Sample_3	profiled_sample_3.sp.txt
……
Sample_N	profiled_sample_N.sp.txt
```

The first column is the sample ID and the second column is the path of profiling result file. Then run:
```
MS-single-to-table -l samples.list.txt -o samples.sp.table
```
This step can be ignored if you have already obtained the species-level relative abundance table by MetaPhlAn2 (e.g. [Example dataset](#example-dataset) in below).

c.Make custom reference:
```
MS-make -i tree.nwk -r taxonomy_annotation.txt -o ref.dms
```
d. Generate the distance matrix:
```
MS-comp-taxa-dynamic -T samples.sp.table -o samples.sp.dist [-D ref.dms]
```
or you can generate the distance matrix with custom reference:
```
MS-comp-taxa-dynamic -T samples.sp.table -o samples.sp.dist -D ref.dms
```
The output file “samples.sp.dist” is the pairwise distance matrix. 
# Example dataset
Here we provide a demo dataset (Synthetic Dataset 1) with species abundance of 40 synthetic metagenomic samples in “example” folder. In this package, “dataset1.sp.abd” is the relative abundance on species-level, and “dataset1.meta” is the group information of the samples.

To run the demo, you can either:
```
cd example
sh Readme
```
or type the following command:
```
MS-comp-taxa-dynamic -T dataset1.sp.abd -o dataset1.sp.abd.dist
```
Then the output file “dataset1.sp.abd.dist” is the pairwise distance of the 40 samples.

This demo run should take less than 1 minute on a recommended computer.

# Tools in this package
a. MS-comp-taxa-dynamic

It calculates the dynamic meta-storms distance matrix among metagenomes. Run:
```
MS-comp-taxa-dynamic -h
```
for detailed parameters.

b. MS-comp-taxa

It calculates the regular meta-storms distance matrix among metagenomes. This method ignores the unclassified organisms in metagenomes. Run:
```
MS-comp-taxa -h
```
for detailed parameters.

c. MS-single-to-table

It merges multiple single-sample-output files to relative abundance table. See “ [Merge multiple output files to species-level relative abundance table](#usage)” above for example usage, or run:
```
MS-single-to-table -h
```
for detailed parameters.

d. MS-table-to-single

It splits relative abundance table to multiple single-sample-output files. Run:
```
MS-table-to-single -h
```
for detailed parameters.

e. MS-make-ref
It generates custom reference with custom taxonoic profiles. Run
```
MS-make-ref -h
```
for detailed parameters.


# Supplementary

[Synthetic Dataset 1](http://bioinfo.single-cell.cn/Released_Software/dynamic-meta-storms/data/synthetic_dataset_1.tar.gz) contains 40 synthetic metagenomes that are derived from 48 bacteria species.

[Synthetic Dataset 2](http://bioinfo.single-cell.cn/Released_Software/dynamic-meta-storms/data/synthetic_dataset_2.tar.gz) contains 100,000 synthetic metagenomes that are derived from 3,688 bacteria species.

[Real Dataset 1](http://bioinfo.single-cell.cn/Released_Software/dynamic-meta-storms/data/actual_dataset_1.tar.gz) contains 2,355 actual human metagenomes produced by Human Microbiome Project Phase 1 (version 2).


[Real Dataset 2](http://bioinfo.single-cell.cn/Released_Software/dynamic-meta-storms/data/actual_dataset_2.tar.gz)  contains 24 real enivronmental metagenomes procuded by MetaSUB.
