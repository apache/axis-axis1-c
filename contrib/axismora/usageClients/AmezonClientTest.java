import java.net.URL;

import junit.framework.TestCase;

import com.bookshop.soap.AmazonSearchPort;
import com.bookshop.soap.AmazonSearchServiceLocator;

/**
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class AmezonClientTest extends TestCase{
	public void testAmezonClient()throws Exception{
		AmazonSearchServiceLocator service = new AmazonSearchServiceLocator(); 
	    // Now use the service to get a stub which implements the SDI.
		AmazonSearchPort port = service.getAmazonSearchPort(new URL(AllUsageTest.END_POINT_URI));
        // Make the actual call
		com.bookshop.soap.ModifyShoppingCartItemsRequest req  = new com.bookshop.soap.ModifyShoppingCartItemsRequest();
		com.bookshop.soap.ShoppingCart res = port.modifyShoppingCartItemsRequest(req);
		
		System.out.println(res.getCartId());
		System.out.println(res.getHMAC());
		System.out.println(res.getPurchaseUrl());
		System.out.println(res.getItems());
		System.out.println("------- test 1 sucseeeded -------"); 
		
		com.bookshop.soap.KeywordRequest req2  = new com.bookshop.soap.KeywordRequest();
		com.bookshop.soap.ProductInfo res2 = port.keywordSearchRequest(req2);
		System.out.println(res2);
		System.out.println(res2.getListName());
		System.out.println(res2.getTotalPages());
		System.out.println(res2.getTotalResults());
		System.out.println(res2.getDetails());
	
		System.out.println(" ------ test 2 suceeded -----------");
		
		com.bookshop.soap.ActorRequest req3 = new com.bookshop.soap.ActorRequest(); 
		com.bookshop.soap.ProductInfo res3 = port.actorSearchRequest(req3);
		System.out.println(res3);
		System.out.println(res3.getListName());
		System.out.println(res3.getTotalPages());
		System.out.println(res3.getTotalResults());
		System.out.println(res3.getDetails());	
		System.out.println(" ------ test 3 suceeded -----------");
		
		com.bookshop.soap.ArtistRequest req4 = new com.bookshop.soap.ArtistRequest(); 
		com.bookshop.soap.ProductInfo res4 = port.artistSearchRequest(req4);
		System.out.println(res4);
		System.out.println(res4.getListName());
		System.out.println(res4.getTotalPages());
		System.out.println(res4.getTotalResults());
		System.out.println(res4.getDetails());			
		System.out.println(" ------ test 4 suceeded -----------");
				
		com.bookshop.soap.AsinRequest req5 = new com.bookshop.soap.AsinRequest(); 
		com.bookshop.soap.ProductInfo res5 = port.asinSearchRequest(req5);
		System.out.println(res5);
		System.out.println(res5.getListName());
		System.out.println(res5.getTotalPages());
		System.out.println(res5.getTotalResults());
		System.out.println(res5.getDetails());			
		System.out.println(" ------ test 5 suceeded -----------");
		
		com.bookshop.soap.AuthorRequest req6 = new com.bookshop.soap.AuthorRequest(); 
		com.bookshop.soap.ProductInfo res6 = port.authorSearchRequest(req6);
		System.out.println(res6);
		System.out.println(res6.getListName());
		System.out.println(res6.getTotalPages());
		System.out.println(res6.getTotalResults());
		System.out.println(res6.getDetails());			
		System.out.println(" ------ test 6 suceeded -----------");

        com.bookshop.soap.BlendedRequest req7 = new com.bookshop.soap.BlendedRequest();
        com.bookshop.soap.ProductLine[] res7 = port.blendedSearchRequest(req7);
        System.out.println(res7);
        System.out.println(res7[0].getMode());
        System.out.println(res7[0].getProductInfo());
        System.out.println(" ------ test 7 suceeded -----------");
        
		com.bookshop.soap.BrowseNodeRequest req8 = new com.bookshop.soap.BrowseNodeRequest(); 
		com.bookshop.soap.ProductInfo res8 = port.browseNodeSearchRequest(req8);
		System.out.println(res8);
		System.out.println(res8.getListName());
		System.out.println(res8.getTotalPages());
		System.out.println(res8.getTotalResults());
		System.out.println(res8.getDetails());			
		System.out.println(" ------ test 8 suceeded -----------");

		com.bookshop.soap.DirectorRequest req9 = new com.bookshop.soap.DirectorRequest(); 
		com.bookshop.soap.ProductInfo res9 = port.directorSearchRequest(req9);
		System.out.println(res9);
		System.out.println(res9.getListName());
		System.out.println(res9.getTotalPages());
		System.out.println(res9.getTotalResults());
		System.out.println(res9.getDetails());			
		System.out.println(" ------ test 9 suceeded -----------");

		com.bookshop.soap.ListManiaRequest req10 = new com.bookshop.soap.ListManiaRequest(); 
		com.bookshop.soap.ProductInfo res10 = port.listManiaSearchRequest(req10);
		System.out.println(res10);
		System.out.println(res10.getListName());
		System.out.println(res10.getTotalPages());
		System.out.println(res10.getTotalResults());
		System.out.println(res10.getDetails());			
		System.out.println(" ------ test 10 suceeded -----------");

		com.bookshop.soap.ManufacturerRequest req11 = new com.bookshop.soap.ManufacturerRequest(); 
		com.bookshop.soap.ProductInfo res11 = port.manufacturerSearchRequest(req11);
		System.out.println(res11);
		System.out.println(res11.getListName());
		System.out.println(res11.getTotalPages());
		System.out.println(res11.getTotalResults());
		System.out.println(res11.getDetails());			
		System.out.println(" ------ test 11 suceeded -----------");

		com.bookshop.soap.PowerRequest req12 = new com.bookshop.soap.PowerRequest(); 
		com.bookshop.soap.ProductInfo res12 = port.powerSearchRequest(req12);
		System.out.println(res12);
		System.out.println(res12.getListName());
		System.out.println(res12.getTotalPages());
		System.out.println(res12.getTotalResults());
		System.out.println(res12.getDetails());			
		System.out.println(" ------ test 12 suceeded -----------");

		com.bookshop.soap.SimilarityRequest req13 = new com.bookshop.soap.SimilarityRequest(); 
		com.bookshop.soap.ProductInfo res13 = port.similaritySearchRequest(req13);
		System.out.println(res13);
		System.out.println(res13.getListName());
		System.out.println(res13.getTotalPages());
		System.out.println(res13.getTotalResults());
		System.out.println(res13.getDetails());			
		System.out.println(" ------ test 13 suceeded -----------");

		com.bookshop.soap.UpcRequest req14 = new com.bookshop.soap.UpcRequest(); 
		com.bookshop.soap.ProductInfo res14 = port.upcSearchRequest(req14);
		System.out.println(res14);
		System.out.println(res14.getListName());
		System.out.println(res14.getTotalPages());
		System.out.println(res14.getTotalResults());
		System.out.println(res14.getDetails());			
		System.out.println(" ------ test 14 suceeded -----------");

		com.bookshop.soap.WishlistRequest req15 = new com.bookshop.soap.WishlistRequest(); 
		com.bookshop.soap.ProductInfo res15 = port.wishlistSearchRequest(req15);
		System.out.println(res15);
		System.out.println(res15.getListName());
		System.out.println(res15.getTotalPages());
		System.out.println(res15.getTotalResults());
		System.out.println(res15.getDetails());			
		System.out.println(" ------ test 15 suceeded -----------");

		com.bookshop.soap.AddShoppingCartItemsRequest req16  = new com.bookshop.soap.AddShoppingCartItemsRequest();
		com.bookshop.soap.ShoppingCart res16 = port.addShoppingCartItemsRequest(req16);
		
		System.out.println(res16.getCartId());
		System.out.println(res16.getHMAC());
		System.out.println(res16.getPurchaseUrl());
		System.out.println(res16.getItems());
		System.out.println("------- test 16 sucseeeded -------");
		
		com.bookshop.soap.RemoveShoppingCartItemsRequest req17  = new com.bookshop.soap.RemoveShoppingCartItemsRequest();
		com.bookshop.soap.ShoppingCart res17 = port.removeShoppingCartItemsRequest(req17);
		
		System.out.println(res17.getCartId());
		System.out.println(res17.getHMAC());
		System.out.println(res17.getPurchaseUrl());
		System.out.println(res17.getItems());
		System.out.println("------- test 17 sucseeeded -------");		
	
		com.bookshop.soap.ClearShoppingCartRequest req18  = new com.bookshop.soap.ClearShoppingCartRequest();
		com.bookshop.soap.ShoppingCart res18 = port.clearShoppingCartRequest(req18);
		
		System.out.println(res18.getCartId());
		System.out.println(res18.getHMAC());
		System.out.println(res18.getPurchaseUrl());
		System.out.println(res18.getItems());
		System.out.println("------- test 18 sucseeeded -------");
		
		com.bookshop.soap.ExchangeRequest req19 = new com.bookshop.soap.ExchangeRequest();
		com.bookshop.soap.ListingProductDetails res19 = port.exchangeSearchRequest(req19);
		System.out.println(res19);
		System.out.println(res19.getExchangeAsin());
		System.out.println(res19.getExchangeAvailability());
		System.out.println(res19.getExchangeCondition());
		System.out.println(res19.getExchangeConditionType());
		System.out.println(res19.getExchangeEndDate());
		System.out.println(res19.getExchangeFeaturedCategory());
		System.out.println(res19.getExchangeId());
		System.out.println(res19.getExchangeOfferingType());
		System.out.println(res19.getExchangePrice());
		System.out.println(res19.getExchangePrice());
		System.out.println(res19.getExchangeQuantity());
		System.out.println(res19.getExchangeQuantityAllocated());
		System.out.println(res19.getExchangeSellerCountry());
		System.out.println(res19.getExchangeSellerId());
		System.out.println(res19.getExchangeSellerNickname());
		System.out.println(res19.getExchangeSellerRating());
		System.out.println(res19.getExchangeSellerState());
		System.out.println(res19.getExchangeStartDate());
		System.out.println(res19.getExchangeStatus());
		System.out.println(res19.getExchangeTinyImage());
		System.out.println(res19.getExchangeTitle());
		System.out.println(res19.getListingId());
		System.out.println("------- test 19 sucseeeded -------");
				
		com.bookshop.soap.MarketplaceRequest req20 = new com.bookshop.soap.MarketplaceRequest();
		com.bookshop.soap.MarketplaceSearch res20 = port.marketplaceSearchRequest(req20);
		System.out.println(res20);
		System.out.println(res20.getMarketplaceSearchDetails());
		System.out.println("------- test 20 sucseeeded -------");
				
		com.bookshop.soap.SellerProfileRequest req21 = new com.bookshop.soap.SellerProfileRequest();
		com.bookshop.soap.SellerProfile res21 = port.sellerProfileSearchRequest(req21);
		System.out.println(res21);
		System.out.println(res21.getSellerProfileDetails());
		System.out.println("------- test 21 sucseeeded -------");
				
		com.bookshop.soap.SellerRequest req22 = new com.bookshop.soap.SellerRequest();
		com.bookshop.soap.SellerSearch res22 = port.sellerSearchRequest(req22);
		System.out.println(res22);
		System.out.println(res22.getSellerSearchDetails());
		System.out.println("------- test 22 sucseeeded -------");
	}	
	public static void main(String[] args)throws Exception{
		AmezonClientTest ac = new AmezonClientTest();
		ac.testAmezonClient();		
	}
}
