/**
 * AmazonSearchPort.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis WSDL2Java emitter.
 */

package com.bookshop.soap;

public interface AmazonSearchPort extends java.rmi.Remote {
    public com.bookshop.soap.ProductInfo keywordSearchRequest(com.bookshop.soap.KeywordRequest keywordSearchRequest) throws java.rmi.RemoteException;
    public com.bookshop.soap.ProductInfo powerSearchRequest(com.bookshop.soap.PowerRequest powerSearchRequest) throws java.rmi.RemoteException;
    public com.bookshop.soap.ProductInfo browseNodeSearchRequest(com.bookshop.soap.BrowseNodeRequest browseNodeSearchRequest) throws java.rmi.RemoteException;
    public com.bookshop.soap.ProductInfo asinSearchRequest(com.bookshop.soap.AsinRequest asinSearchRequest) throws java.rmi.RemoteException;
    public com.bookshop.soap.ProductLine[] blendedSearchRequest(com.bookshop.soap.BlendedRequest blendedSearchRequest) throws java.rmi.RemoteException;
    public com.bookshop.soap.ProductInfo upcSearchRequest(com.bookshop.soap.UpcRequest upcSearchRequest) throws java.rmi.RemoteException;
    public com.bookshop.soap.ProductInfo authorSearchRequest(com.bookshop.soap.AuthorRequest authorSearchRequest) throws java.rmi.RemoteException;
    public com.bookshop.soap.ProductInfo artistSearchRequest(com.bookshop.soap.ArtistRequest artistSearchRequest) throws java.rmi.RemoteException;
    public com.bookshop.soap.ProductInfo actorSearchRequest(com.bookshop.soap.ActorRequest actorSearchRequest) throws java.rmi.RemoteException;
    public com.bookshop.soap.ProductInfo manufacturerSearchRequest(com.bookshop.soap.ManufacturerRequest manufacturerSearchRequest) throws java.rmi.RemoteException;
    public com.bookshop.soap.ProductInfo directorSearchRequest(com.bookshop.soap.DirectorRequest directorSearchRequest) throws java.rmi.RemoteException;
    public com.bookshop.soap.ProductInfo listManiaSearchRequest(com.bookshop.soap.ListManiaRequest listManiaSearchRequest) throws java.rmi.RemoteException;
    public com.bookshop.soap.ProductInfo wishlistSearchRequest(com.bookshop.soap.WishlistRequest wishlistSearchRequest) throws java.rmi.RemoteException;
    public com.bookshop.soap.ListingProductDetails exchangeSearchRequest(com.bookshop.soap.ExchangeRequest exchangeSearchRequest) throws java.rmi.RemoteException;
    public com.bookshop.soap.MarketplaceSearch marketplaceSearchRequest(com.bookshop.soap.MarketplaceRequest marketplaceSearchRequest) throws java.rmi.RemoteException;
    public com.bookshop.soap.SellerProfile sellerProfileSearchRequest(com.bookshop.soap.SellerProfileRequest sellerProfileSearchRequest) throws java.rmi.RemoteException;
    public com.bookshop.soap.SellerSearch sellerSearchRequest(com.bookshop.soap.SellerRequest sellerSearchRequest) throws java.rmi.RemoteException;
    public com.bookshop.soap.ProductInfo similaritySearchRequest(com.bookshop.soap.SimilarityRequest similaritySearchRequest) throws java.rmi.RemoteException;
    public com.bookshop.soap.ShoppingCart getShoppingCartRequest(com.bookshop.soap.GetShoppingCartRequest getShoppingCartRequest) throws java.rmi.RemoteException;
    public com.bookshop.soap.ShoppingCart clearShoppingCartRequest(com.bookshop.soap.ClearShoppingCartRequest clearShoppingCartRequest) throws java.rmi.RemoteException;
    public com.bookshop.soap.ShoppingCart addShoppingCartItemsRequest(com.bookshop.soap.AddShoppingCartItemsRequest addShoppingCartItemsRequest) throws java.rmi.RemoteException;
    public com.bookshop.soap.ShoppingCart removeShoppingCartItemsRequest(com.bookshop.soap.RemoveShoppingCartItemsRequest removeShoppingCartItemsRequest) throws java.rmi.RemoteException;
    public com.bookshop.soap.ShoppingCart modifyShoppingCartItemsRequest(com.bookshop.soap.ModifyShoppingCartItemsRequest modifyShoppingCartItemsRequest) throws java.rmi.RemoteException;
}
