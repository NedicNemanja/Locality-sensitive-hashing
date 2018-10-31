# Locality-sensitive-hashing

A implementation of LSH with multiple Hashtable and LSH using a Hypercube structure for the Hashtable.
Metrics used for comparing vector distances: Euclidean & Cosine Similarity.


Read TheorySlides.pdf to get familiar with the problem's and the algorithms.

Read Project_README.pdf for details on implementation and conclusions regarding the efficiency.

If you have a dataset file ready but it has no id's for the vectors use this to add id's.


``` awk '{print NR,$0}' ./siftsmall/query_small | sed -e 's/^/id/' >> new_file ```
