# NOvA validation

This repository contains visualisation code for the NOvA visualisation framework, providing simple general-purpose utilities for easily visualising distributions.

## Instructions

The example plotting macro can be run with
```
root -b -q example.C
```

The contents of the validation root file can be visualised in a browser with
```
rootbrowse valid.hist.root
```

## Roadmap

- Simple plotting utilities
  - Function for visualising 1D histograms (18th Feb)
  - Function for visualising 2D histograms (25th Feb)
- Plot multiple distributions
  - Function to plot multiple 1D histograms on the same canvas (4th March)
  - Function to plot multiple 1D histograms as a stacked histogram (11th March)
  - Function to plot ratios of 1D histograms to reference distribution (18th March)
- Multiple histogram plotting at file level
  - Plot the same histograms from multiple files on the same canvas (27th May)
- Document forming
  - Utility to generate LaTeX document format (3rd June)
  - Utility to generate LaTeX slide format (10th June)

## Resources

[Learn Git in 15 Minutes](https://www.youtube.com/watch?v=USjZcfj8yxE)
