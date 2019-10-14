#################################################################
# Function: Ape 
# Call: Rscript New_tree.R -i old.nwk -o new.nwk [-l T/F -o outfile -a axesfile]
# R packages used: ape
# Update: 2019-10-09,Jing Gongchao
# Last update: 2019-10-09, Jing Gongchao
#################################################################

## install necessary libraries
p <- c("optparse","ape")
usePackage <- function(p) {
  if (!is.element(p, installed.packages()[,1]))
    install.packages(p, dep=TRUE, repos="http://cran.us.r-project.org/")
  suppressWarnings(suppressMessages(invisible(require(p, character.only=TRUE))))
}
invisible(lapply(p, usePackage))

## clean R environment
rm(list = ls())
setwd('./')

## parsing arguments
args <- commandArgs(trailingOnly=TRUE)

# make option list and parse command line
option_list <- list(  
  make_option(c("-i", "--nwk_file"), type="character", help="Input tree file [Required]"),
  make_option(c("-o", "--outfile"), type="character", default='new.nwk', help="Output PCoA [default %default]")
)
opts <- parse_args(OptionParser(option_list=option_list), args=args)

# paramenter checking
if(is.null(opts$nwk_file)) stop('Please input a nwk file')




# import tree file
tr <- read.tree(file=opts$nwk_file)

#is_binary
is_if <- is.binary(multi2di(tr))

#write tree
write.tree(tr,opts$outfile)
