#################################################################
# Function: Configurate the R packages for Parallel-META
# Call: Rscript RM_Config.R
# Authors: Xiaoquan Su
# Last update: 2017-11-01, Xiaoquan Su
# Bioinformatics Group, Single-Cell Research Center, QIBEBT, CAS
#################################################################

## install necessary libraries
p <- c("ape")
usePackage <- function(p) {
  if (!is.element(p, installed.packages()[,1]))
    install.packages(p, dep=TRUE, repos="http://cran.us.r-project.org/")
  suppressWarnings(suppressMessages(invisible(require(p, character.only=TRUE))))
}
invisible(lapply(p, usePackage))


#  check environment variables
Env <-Sys.getenv("DynamicMetaStorms")
if(nchar(Env)<1){
  cat('Please set the environment variable \"DynamicMetaStorms\" to the directory\n')
 }

