/**
 * MyGoogleSearchResult.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2alpha Feb 10, 2004 (12:04:50 GMT+06:00) WSDL2Java emitter.
 */

package org.objectweb.wssample.gen.google;

public class MyGoogleSearchResult  implements java.io.Serializable {
    private boolean documentFiltering;
    private java.lang.String searchComments;
    private int estimatedTotalResultsCount;
    private boolean estimateIsExact;
    private org.objectweb.wssample.gen.google.ResultElement[] resultElements;
    private java.lang.String searchQuery;
    private int startIndex;
    private int endIndex;
    private java.lang.String searchTips;
    private org.objectweb.wssample.gen.google.DirectoryCategory[] directoryCategories;
    private double searchTime;

    public MyGoogleSearchResult() {
    }


    /**
     * Gets the documentFiltering value for this MyGoogleSearchResult.
     * 
     * @return documentFiltering 
     */
    public boolean isDocumentFiltering() {
        return documentFiltering;
    }


    /**
     * Sets the documentFiltering value for this MyGoogleSearchResult.
     * 
     * @param documentFiltering 
     */
    public void setDocumentFiltering(boolean documentFiltering) {
        this.documentFiltering = documentFiltering;
    }


    /**
     * Gets the searchComments value for this MyGoogleSearchResult.
     * 
     * @return searchComments 
     */
    public java.lang.String getSearchComments() {
        return searchComments;
    }


    /**
     * Sets the searchComments value for this MyGoogleSearchResult.
     * 
     * @param searchComments 
     */
    public void setSearchComments(java.lang.String searchComments) {
        this.searchComments = searchComments;
    }


    /**
     * Gets the estimatedTotalResultsCount value for this MyGoogleSearchResult.
     * 
     * @return estimatedTotalResultsCount 
     */
    public int getEstimatedTotalResultsCount() {
        return estimatedTotalResultsCount;
    }


    /**
     * Sets the estimatedTotalResultsCount value for this MyGoogleSearchResult.
     * 
     * @param estimatedTotalResultsCount 
     */
    public void setEstimatedTotalResultsCount(int estimatedTotalResultsCount) {
        this.estimatedTotalResultsCount = estimatedTotalResultsCount;
    }


    /**
     * Gets the estimateIsExact value for this MyGoogleSearchResult.
     * 
     * @return estimateIsExact 
     */
    public boolean isEstimateIsExact() {
        return estimateIsExact;
    }


    /**
     * Sets the estimateIsExact value for this MyGoogleSearchResult.
     * 
     * @param estimateIsExact 
     */
    public void setEstimateIsExact(boolean estimateIsExact) {
        this.estimateIsExact = estimateIsExact;
    }


    /**
     * Gets the resultElements value for this MyGoogleSearchResult.
     * 
     * @return resultElements 
     */
    public org.objectweb.wssample.gen.google.ResultElement[] getResultElements() {
        return resultElements;
    }


    /**
     * Sets the resultElements value for this MyGoogleSearchResult.
     * 
     * @param resultElements 
     */
    public void setResultElements(org.objectweb.wssample.gen.google.ResultElement[] resultElements) {
        this.resultElements = resultElements;
    }


    /**
     * Gets the searchQuery value for this MyGoogleSearchResult.
     * 
     * @return searchQuery 
     */
    public java.lang.String getSearchQuery() {
        return searchQuery;
    }


    /**
     * Sets the searchQuery value for this MyGoogleSearchResult.
     * 
     * @param searchQuery 
     */
    public void setSearchQuery(java.lang.String searchQuery) {
        this.searchQuery = searchQuery;
    }


    /**
     * Gets the startIndex value for this MyGoogleSearchResult.
     * 
     * @return startIndex 
     */
    public int getStartIndex() {
        return startIndex;
    }


    /**
     * Sets the startIndex value for this MyGoogleSearchResult.
     * 
     * @param startIndex 
     */
    public void setStartIndex(int startIndex) {
        this.startIndex = startIndex;
    }


    /**
     * Gets the endIndex value for this MyGoogleSearchResult.
     * 
     * @return endIndex 
     */
    public int getEndIndex() {
        return endIndex;
    }


    /**
     * Sets the endIndex value for this MyGoogleSearchResult.
     * 
     * @param endIndex 
     */
    public void setEndIndex(int endIndex) {
        this.endIndex = endIndex;
    }


    /**
     * Gets the searchTips value for this MyGoogleSearchResult.
     * 
     * @return searchTips 
     */
    public java.lang.String getSearchTips() {
        return searchTips;
    }


    /**
     * Sets the searchTips value for this MyGoogleSearchResult.
     * 
     * @param searchTips 
     */
    public void setSearchTips(java.lang.String searchTips) {
        this.searchTips = searchTips;
    }


    /**
     * Gets the directoryCategories value for this MyGoogleSearchResult.
     * 
     * @return directoryCategories 
     */
    public org.objectweb.wssample.gen.google.DirectoryCategory[] getDirectoryCategories() {
        return directoryCategories;
    }


    /**
     * Sets the directoryCategories value for this MyGoogleSearchResult.
     * 
     * @param directoryCategories 
     */
    public void setDirectoryCategories(org.objectweb.wssample.gen.google.DirectoryCategory[] directoryCategories) {
        this.directoryCategories = directoryCategories;
    }


    /**
     * Gets the searchTime value for this MyGoogleSearchResult.
     * 
     * @return searchTime 
     */
    public double getSearchTime() {
        return searchTime;
    }


    /**
     * Sets the searchTime value for this MyGoogleSearchResult.
     * 
     * @param searchTime 
     */
    public void setSearchTime(double searchTime) {
        this.searchTime = searchTime;
    }

    private java.lang.Object __equalsCalc = null;
    public synchronized boolean equals(java.lang.Object obj) {
        if (!(obj instanceof MyGoogleSearchResult)) return false;
        MyGoogleSearchResult other = (MyGoogleSearchResult) obj;
        if (obj == null) return false;
        if (this == obj) return true;
        if (__equalsCalc != null) {
            return (__equalsCalc == obj);
        }
        __equalsCalc = obj;
        boolean _equals;
        _equals = true && 
            this.documentFiltering == other.isDocumentFiltering() &&
            ((this.searchComments==null && other.getSearchComments()==null) || 
             (this.searchComments!=null &&
              this.searchComments.equals(other.getSearchComments()))) &&
            this.estimatedTotalResultsCount == other.getEstimatedTotalResultsCount() &&
            this.estimateIsExact == other.isEstimateIsExact() &&
            ((this.resultElements==null && other.getResultElements()==null) || 
             (this.resultElements!=null &&
              java.util.Arrays.equals(this.resultElements, other.getResultElements()))) &&
            ((this.searchQuery==null && other.getSearchQuery()==null) || 
             (this.searchQuery!=null &&
              this.searchQuery.equals(other.getSearchQuery()))) &&
            this.startIndex == other.getStartIndex() &&
            this.endIndex == other.getEndIndex() &&
            ((this.searchTips==null && other.getSearchTips()==null) || 
             (this.searchTips!=null &&
              this.searchTips.equals(other.getSearchTips()))) &&
            ((this.directoryCategories==null && other.getDirectoryCategories()==null) || 
             (this.directoryCategories!=null &&
              java.util.Arrays.equals(this.directoryCategories, other.getDirectoryCategories()))) &&
            this.searchTime == other.getSearchTime();
        __equalsCalc = null;
        return _equals;
    }

    private boolean __hashCodeCalc = false;
    public synchronized int hashCode() {
        if (__hashCodeCalc) {
            return 0;
        }
        __hashCodeCalc = true;
        int _hashCode = 1;
        _hashCode += (isDocumentFiltering() ? Boolean.TRUE : Boolean.FALSE).hashCode();
        if (getSearchComments() != null) {
            _hashCode += getSearchComments().hashCode();
        }
        _hashCode += getEstimatedTotalResultsCount();
        _hashCode += (isEstimateIsExact() ? Boolean.TRUE : Boolean.FALSE).hashCode();
        if (getResultElements() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getResultElements());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getResultElements(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        if (getSearchQuery() != null) {
            _hashCode += getSearchQuery().hashCode();
        }
        _hashCode += getStartIndex();
        _hashCode += getEndIndex();
        if (getSearchTips() != null) {
            _hashCode += getSearchTips().hashCode();
        }
        if (getDirectoryCategories() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getDirectoryCategories());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getDirectoryCategories(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        _hashCode += new Double(getSearchTime()).hashCode();
        __hashCodeCalc = false;
        return _hashCode;
    }

}
