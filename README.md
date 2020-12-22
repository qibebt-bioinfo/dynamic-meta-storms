# Dynamic Meta-Storms

![Version](https://img.shields.io/badge/Version-1.1-brightgreen)
![Release date](https://img.shields.io/badge/Release%20date-Dec.%207%2C%202020-brightgreen.svg)



## Contents

- [Introduction](#introduction)
- [System Requirement and dependency](#system-requirement-and-dependency)
- [Installation guide](#installation-guide)
- [Usage](#usage)
- [Example dataset](#example-dataset)
- [Tools in this package](#tools-in-this-package)
- [Supplementary](#supplementary)
- [Citation](#citation)

# Introduction

Dynamic Meta-Storms calculates comprehensive taxonomic and phylogenetic distances/dissimilarities of shotgun metagenomes at the species level. It takes the species-level profiling results (e.g. MetaPhlAn2) as input, and compares metagenomes on the species-level with both taxonomy and phylogeny profiles. When comparing samples, for organisms that can be identified by species, Dynamic Meta-Storms measures their dissimilarity based on the species-level phylogeny tree using the Meta-Storms algorithm; for unclassified species, it dynamically locates such organisms to the virtual internal nodes that account for all the sub-branches under the same taxonomy.

# System Requirement and dependency

## Hardware Requirements

Dynamic Meta-Storms only requires a standard computer with sufficient RAM to support the operations defined by a user. For typical users, this would be a computer with about 2 GB of RAM. For optimal performance, we recommend a computer with the following specs:

  RAM: 8+ GB  
  CPU: 4+ cores, 3.3+ GHz/core

## Software Requirements

OpenMP library is the C/C++ parallel computing library. Most Linux releases have OpenMP already been installed in the system. In Mac OS X, to install the compiler that supports OpenMP, we recommend using the Homebrew package manager:
```shell
brew install gcc
```

# Installation guide

## Automatic Installation (recommended)

At present, Dynamic Meta-Storms provides a fully automatic installer for easy installation.

**a. Download the package**
```
git clone https://github.com/qibebt-bioinfo/dynamic-meta-storms.git	
```

**b. Install by installer**
```
cd dynamic-meta-storms
source install.sh
```

The package should take less than 1 minute to install on a computer with the specifications recommended above.

The example dataset could be found at “example” folder. Check the “example/Readme” for details about the demo run.

## Manual Installation

If the automatic installer fails, Dynamic Meta-Storms can still be installed manually.

**a. Download the package**
```
git clone https://github.com/qibebt-bioinfo/dynamic-meta-storms.git	
```

**b. Configure the environment variables (the default environment variable configuration file is “~/.bashrc”)**
```
export DynamicMetaStorms=Path to Dynamic Meta-Storms
export PATH=”$PATH:$DynamicMetaStorms/bin/”
source ~/.bashrc
```
**c. Compile the source code**
```
cd dynamic-meta-storms
make
```

# Usage
**a. Metagenomic species-level profiling by MetaPhlAn2**

Dynamic Meta-Storms takes the species-level profiling results of MetaPhlAn2 as input. You can either start from the metagenomics sequence file:
```
metaphlan2.py sample_1.fasta --input_type fasta --tax_lev s --ignore_viruses --ignore_eukaryotes --ignore_archaea > profiled_sample_1.sp.txt
```
or you can start from the intermediate BowTie2 output by MetaPhlAn2:
```
metaphlan2.py sample_1.bowtie2.bz2 --input_type bowtie2out --tax_lev s --ignore_viruses --ignore_eukaryotes --ignore_archaea > profiled_sample_1.sp.txt
```
This step can be ignored if you have already obtained the species-level relative abundance table by MetaPhlAn2 (e.g. [Example dataset](#example-dataset) in below).

**b. Merge multiple output files to species-level relative abundance table**

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

**c. Compute the distance matrix**

In this step, you can compute distance matrix for relative abundance table by
```
MS-comp-taxa-dynamic -T samples.sp.table -o samples.sp.dist
```
The output file “samples.sp.dist” is the pairwise distance matrix computed with MetaPhlAn2 tree and taxonomy.

The reference trees of MetaPhlAn2 and MetaPhlAn3 have been integrated in the package, and the default is MetaPhlAn2. If your taxonomy abundance table was profiled by MetaPhlAn3, You can also use the MetaPhlAn3 as the reference by the -D option.
```
MS-comp-taxa-dynamic -D M -T samples.sp.table -o samples.sp.dist
```

**d. Make a customized reference**

To make a customized reference, please input a reference phylogeny tree in Newick format (tip nodes are species names), and a reference full taxonomy of the species in tabular format.
```
MS-make-ref -i tree.newick -r tree.taxonomy -o tree.dms
```
MS-make-ref needs [R](https://www.r-project.org) and package "[ape](https://cran.r-project.org/web/packages/ape/index.html)". The input taxonomy format is
```
Kingdom Phylum  Class   Order   Family  Genus   Species
k__Archaea p__Euryarchaeota c__Methanopyri o__Methanopyrales f__Methanopyraceae g__Methanopyrus s__Methanopyrus_kandleri
k__Archaea p__Euryarchaeota c__Methanobacteria o__Methanobacteriales f__Methanothermaceae g__Methanothermus  s__Methanothermus_fervidus
k__Archaea p__Euryarchaeota c__Methanobacteria o__Methanobacteriales f__Methanobacteriaceae g__Methanothermobacter s__Methanothermobacter_marburgensis
```
Then you can compute the distance matrix with the customized reference:
```
MS-comp-taxa-dynamic -D tree.dms -T samples.sp.table -o samples.sp.dist
```
The source files of both MetaPhlAn2 and MetaPhlAn3 tree and taxonomy for example of customized reference is available as [Supplementary](#supplementary).

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
**a. MS-comp-taxa-dynamic**

It calculates the dynamic meta-storms distance matrix among metagenomes. Run:
```
MS-comp-taxa-dynamic -h
```
for detailed parameters.

**b. MS-comp-taxa**

It calculates the regular meta-storms distance matrix among metagenomes. This method ignores the unclassified organisms in metagenomes. Run:
```
MS-comp-taxa -h
```
for detailed parameters.

**c. MS-single-to-table**

It merges multiple single-sample-output files to relative abundance table. See “ [Merge multiple output files to species-level relative abundance table](#usage)” above for example usage, or run:
```
MS-single-to-table -h
```
for detailed parameters.

**d. MS-table-to-single**

It splits relative abundance table to multiple single-sample-output files. Run:
```
MS-table-to-single -h
```
for detailed parameters.

**e. MS-make-ref**

MS-make-ref needs [R](https://www.r-project.org) and package "[ape](https://cran.r-project.org/web/packages/ape/index.html)". It generates customized reference with input phylogeny tree and taxonomy. Run：
```
MS-make-ref -h
```
for detailed parameters.

# Supplementary

[Synthetic Dataset 1](http://bioinfo.single-cell.cn/Released_Software/dynamic-meta-storms/data/synthetic_dataset_1.tar.gz) contains 40 synthetic metagenomes that are derived from 48 bacteria species.

[Synthetic Dataset 2](http://bioinfo.single-cell.cn/Released_Software/dynamic-meta-storms/data/synthetic_dataset_2.tar.gz) contains 100,000 synthetic metagenomes that are derived from 3,688 bacteria species.

[Real Dataset 1](http://bioinfo.single-cell.cn/Released_Software/dynamic-meta-storms/data/actual_dataset_1.tar.gz) contains 2,355 real human metagenomes produced by Human Microbiome Project Phase 1 (version 2).

[Real Dataset 2](http://bioinfo.single-cell.cn/Released_Software/dynamic-meta-storms/data/actual_dataset_2.tar.gz) contains 24 real environmental metagenomes produced by MetaSUB project.

[Source files](http://bioinfo.single-cell.cn/Released_Software/dynamic-meta-storms/data/metaphlan2.tree.tar.gz) of MetaPhlAn2 tree and taxonomy.

[Source files](http://bioinfo.single-cell.cn/Released_Software/dynamic-meta-storms/data/metaphlan3.tree.tar.gz) of MetaPhlAn3 tree and taxonomy.

# Citations

G. Jing, Y. Zhang, M. Yang, L. Liu, J. Xu, X. Su*, Dynamic Meta-Storms enables comprehensive taxonomic and phylogenetic comparison of shotgun metagenomes at the species level, *Bioinformatics*, 2019
