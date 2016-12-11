---
layout: page
title: Astro codes
permalink: /astro-codes/
---

## EGG: the Empirical Galaxy Generator

Dedicated website: [EGG website](http://cschreib.github.io/egg/)

![EGG logo]({{ site.url }}/assets/egg-logo.svg)

EGG is a suite of tools that can generate mock galaxy catalogs with realistic positions, morphologies and fluxes from the far-ultraviolet to the far-infrared.

The process is based exclusively on empirical relations that are carefully calibrated on state-of-art observations from the deep CANDELS fields, in particular using data from the Hubble-WFC3 camera and Herschel-PACS and SPIRE. The "root" element of the simulation process is the stellar mass of each galaxy, which is used to derive statistically the dust content, star formation rate, optical colors and morphology. The full panchromatic spectrum of the galaxy is generated from this set of parameters, and by construction the resulting flux distributions reproduce accurately the observed ones.

The generated catalogs can be used to produce realistic maps and mock observations to test source extraction codes, to evaluate the reliability of any map-based science (stacking, dropout identification, ...), or even to estimate adequate flux limits for observing proposals.

__Related articles:__

- [C. Schreiber et al. (2016)](http://adsabs.harvard.edu/abs/2016arXiv160605354S): EGG: hatching a mock Universe from empirical prescriptions.

## phy++

Dedicated website: [phy++ website](http://cschreib.github.io/phypp/)

phy++ is a set of library and tools built to provide user friendly data manipulation, as offered in interpreted languages like [IDL](http://www.exelisvis.com/ProductsServices/IDL.aspx) or its open source clone [GDL](http://gnudatalanguage.sourceforge.net/), but with the added benefit of C++, i.e. increased robustness and speed. The philosophy can be summarized with these two statements:

 - *You don't have to pay for what you don't need.*
 - *Your code expresses your intent: one action is one line.*

The library offers the following features:

 - multidimensional arrays with overloaded mathematical operators and
   mathematical functions, providing easy manipulation of tabulated data
 - general purpose functions and algorithms to modify and analyze these data
 - a FITS module allowing read/write operations on FITS images and tables
 - an ASCII module allowing read/write operations on ASCII tables
 - an astrophysics module providing tools such as cosmological calculations,
   template fitting, unit conversions, handling astrometry, cross-matching,
   image regriding, etc.

It relies only on standard C++11, and a couple of well-known libraries for FITS and WCS handling.

Because an example tells more than a thousand words, here is a very simple code sample that prints powers of numbers and saves them in a table:
{% highlight c++ %}
// Include phy++ headers
#include <phypp/phypp.hpp>

// Entry point of the program
int phypp_main(int argc, char* argv[]) {
    // Read some arguments from the command line
    uint_t n = 10;
    double p = 2.0;
    read_args(argc, argv, arg_list(n, p));

    // Create an array containing values from 1 to n
    vec1d v = dindgen(n)+1.0;

    // Compute the 'p'th power of each value
    vec1d pv = pow(v, p);

    // Print them in the terminal
    print(pv);

    // Write these values in an ASCII table
    ascii::write_table_hdr("the_values.dat", 18, ftable(v, pv));
    // Do the same in a FITS table
    fits::write_table("the_values.fits", ftable(v, pv));

    // Exit, no need to worry about freeing memory or whatnot: this is C++!
    return 0;
}
{% endhighlight %}

Once compiled, the executable can be called like this:
{% highlight bash %}
./mypow          # n=10 and p=2 (default)
./mypow n=5      # p=2 (default)
./mypow n=5 p=3
{% endhighlight %}
