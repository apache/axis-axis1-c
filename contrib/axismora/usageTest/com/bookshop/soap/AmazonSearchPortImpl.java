package com.bookshop.soap;
/**
* This is the service class build with the information given
 * by the wsdl file the user should fill the logic here 
 */
public class AmazonSearchPortImpl  {
	public com.bookshop.soap.ProductInfo KeywordSearchRequest(com.bookshop.soap.KeywordRequest param0){
	/*	System.out.println(param0.getDevtag());
		System.out.println(param0.getKeyword());
		System.out.println(param0.getLocale());
		System.out.println(param0.getMode());
		System.out.println(param0.getPage());
		System.out.println(param0.getSort());
		System.out.println(param0.getTag());
		System.out.println(param0.getType());
		System.out.println(param0.getVariations());*/
		try{
			Thread.sleep(20);
		}catch(Exception e){}		
		
		return new com.bookshop.soap.ProductInfo();
	}
	public com.bookshop.soap.ProductInfo PowerSearchRequest(com.bookshop.soap.PowerRequest param0){
		try{
			Thread.sleep(20);
		}catch(Exception e){}
		return new com.bookshop.soap.ProductInfo();
	}
	public com.bookshop.soap.ProductInfo BrowseNodeSearchRequest(com.bookshop.soap.BrowseNodeRequest param0){
		try{
			Thread.sleep(20);
		}catch(Exception e){}
			return new com.bookshop.soap.ProductInfo();
	}
	public com.bookshop.soap.ProductInfo AsinSearchRequest(com.bookshop.soap.AsinRequest param0){
		try{
			Thread.sleep(20);
		}catch(Exception e){}
		return new com.bookshop.soap.ProductInfo();
	}
	public com.bookshop.soap.ProductLine[] BlendedSearchRequest(com.bookshop.soap.BlendedRequest param0){
		try{
			Thread.sleep(20);
		}catch(Exception e){}
		return new com.bookshop.soap.ProductLine[]{new com.bookshop.soap.ProductLine()};		
	}
	public com.bookshop.soap.ProductInfo UpcSearchRequest(com.bookshop.soap.UpcRequest param0){
		try{
			Thread.sleep(20);
		}catch(Exception e){}
		return new com.bookshop.soap.ProductInfo();	
	}
	public com.bookshop.soap.ProductInfo AuthorSearchRequest(com.bookshop.soap.AuthorRequest param0){
		try{
			Thread.sleep(20);
		}catch(Exception e){}
		return new com.bookshop.soap.ProductInfo();	
	}
	public com.bookshop.soap.ProductInfo ArtistSearchRequest(com.bookshop.soap.ArtistRequest param0){
		try{
			Thread.sleep(20);
		}catch(Exception e){}
		return new com.bookshop.soap.ProductInfo();	
	}
	public com.bookshop.soap.ProductInfo ActorSearchRequest(com.bookshop.soap.ActorRequest param0){
		try{
			Thread.sleep(20);
		}catch(Exception e){}
		return new com.bookshop.soap.ProductInfo();	
	}
	public com.bookshop.soap.ProductInfo ManufacturerSearchRequest(com.bookshop.soap.ManufacturerRequest param0){
		try{
			Thread.sleep(20);
		}catch(Exception e){}
		return new com.bookshop.soap.ProductInfo();	
	}
	public com.bookshop.soap.ProductInfo DirectorSearchRequest(com.bookshop.soap.DirectorRequest param0){
		try{
			Thread.sleep(20);
		}catch(Exception e){}
		return new com.bookshop.soap.ProductInfo();	
	}
	public com.bookshop.soap.ProductInfo ListManiaSearchRequest(com.bookshop.soap.ListManiaRequest param0){
		try{
			Thread.sleep(20);
		}catch(Exception e){}
		return new com.bookshop.soap.ProductInfo();	
	}
	public com.bookshop.soap.ProductInfo WishlistSearchRequest(com.bookshop.soap.WishlistRequest param0){
		try{
			Thread.sleep(20);
		}catch(Exception e){}
		return new com.bookshop.soap.ProductInfo();	
	}
	public com.bookshop.soap.ListingProductDetails ExchangeSearchRequest(com.bookshop.soap.ExchangeRequest param0){
		try{
			Thread.sleep(20);
		}catch(Exception e){}
		return new com.bookshop.soap.ListingProductDetails();
	}
	public com.bookshop.soap.MarketplaceSearch MarketplaceSearchRequest(com.bookshop.soap.MarketplaceRequest param0){
		try{
			Thread.sleep(20);
		}catch(Exception e){}
		return new com.bookshop.soap.MarketplaceSearch();	
	}
	public com.bookshop.soap.SellerProfile SellerProfileSearchRequest(com.bookshop.soap.SellerProfileRequest param0){
		try{
			Thread.sleep(20);
		}catch(Exception e){}
		return new com.bookshop.soap.SellerProfile();		
	}
	public com.bookshop.soap.SellerSearch SellerSearchRequest(com.bookshop.soap.SellerRequest param0){
		try{
			Thread.sleep(20);
		}catch(Exception e){}
		return new com.bookshop.soap.SellerSearch();			
	}
	public com.bookshop.soap.ProductInfo SimilaritySearchRequest(com.bookshop.soap.SimilarityRequest param0){
		try{
			Thread.sleep(20);
		}catch(Exception e){}
		return new com.bookshop.soap.ProductInfo();	
	}
	public com.bookshop.soap.ShoppingCart GetShoppingCartRequest(com.bookshop.soap.GetShoppingCartRequest param0){
		try{
			Thread.sleep(20);
		}catch(Exception e){}		
		return new com.bookshop.soap.ShoppingCart();	
	}
	public com.bookshop.soap.ShoppingCart ClearShoppingCartRequest(com.bookshop.soap.ClearShoppingCartRequest param0){
		try{
			Thread.sleep(20);
		}catch(Exception e){}		
		return new com.bookshop.soap.ShoppingCart();		
	}
	public com.bookshop.soap.ShoppingCart AddShoppingCartItemsRequest(com.bookshop.soap.AddShoppingCartItemsRequest param0){
		try{
			Thread.sleep(20);
		}catch(Exception e){}		
		return new com.bookshop.soap.ShoppingCart();		
	}
	public com.bookshop.soap.ShoppingCart RemoveShoppingCartItemsRequest(com.bookshop.soap.RemoveShoppingCartItemsRequest param0){
		try{
			Thread.sleep(20);
		}catch(Exception e){}		
		return new com.bookshop.soap.ShoppingCart();		
	}
	public com.bookshop.soap.ShoppingCart ModifyShoppingCartItemsRequest(com.bookshop.soap.ModifyShoppingCartItemsRequest param0){
		System.out.println(param0.getCartId());
		System.out.println(param0.getDevtag());
		System.out.println(param0.getHMAC());
		System.out.println("locale ="+param0.getLocale());
		System.out.println(param0.getTag()); 
		try{
			Thread.sleep(20);
		}catch(Exception e){}		

		return new com.bookshop.soap.ShoppingCart();
	}}
