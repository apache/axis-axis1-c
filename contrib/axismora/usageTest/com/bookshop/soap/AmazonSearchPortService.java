package com.bookshop.soap;
import org.apache.axis.AxisFault;
import org.apache.axis.message.SOAPFault;
/**
 * This Code is Genarated by the Wrapper Genarator. 
 * This Class act as the Wrapper to invoke the Webservice methods
*/
public class AmazonSearchPortService extends org.apache.axismora.handlers.BasicHandler {
	private com.bookshop.soap.AmazonSearchPortImpl service;

	public AmazonSearchPortService(){
			service = new com.bookshop.soap.AmazonSearchPortImpl();
	}

/*
	This method is called by the Wrapper. 
*/
	public void invoke(org.apache.axismora.MessageContext msgdata){
		 try{
			String methodToCall = msgdata.getMethodName().getLocalPart();
			if("KeywordSearchRequest".equals(methodToCall))
				this.KeywordSearchRequest(msgdata);
		
			else if("PowerSearchRequest".equals(methodToCall))
				this.PowerSearchRequest(msgdata);
		
			else if("BrowseNodeSearchRequest".equals(methodToCall))
				this.BrowseNodeSearchRequest(msgdata);
		
			else if("AsinSearchRequest".equals(methodToCall))
				this.AsinSearchRequest(msgdata);
		
			else if("BlendedSearchRequest".equals(methodToCall))
				this.BlendedSearchRequest(msgdata);
		
			else if("UpcSearchRequest".equals(methodToCall))
				this.UpcSearchRequest(msgdata);
		
			else if("AuthorSearchRequest".equals(methodToCall))
				this.AuthorSearchRequest(msgdata);
		
			else if("ArtistSearchRequest".equals(methodToCall))
				this.ArtistSearchRequest(msgdata);
		
			else if("ActorSearchRequest".equals(methodToCall))
				this.ActorSearchRequest(msgdata);
		
			else if("ManufacturerSearchRequest".equals(methodToCall))
				this.ManufacturerSearchRequest(msgdata);
		
			else if("DirectorSearchRequest".equals(methodToCall))
				this.DirectorSearchRequest(msgdata);
		
			else if("ListManiaSearchRequest".equals(methodToCall))
				this.ListManiaSearchRequest(msgdata);
		
			else if("WishlistSearchRequest".equals(methodToCall))
				this.WishlistSearchRequest(msgdata);
		
			else if("ExchangeSearchRequest".equals(methodToCall))
				this.ExchangeSearchRequest(msgdata);
		
			else if("MarketplaceSearchRequest".equals(methodToCall))
				this.MarketplaceSearchRequest(msgdata);
		
			else if("SellerProfileSearchRequest".equals(methodToCall))
				this.SellerProfileSearchRequest(msgdata);
		
			else if("SellerSearchRequest".equals(methodToCall))
				this.SellerSearchRequest(msgdata);
		
			else if("SimilaritySearchRequest".equals(methodToCall))
				this.SimilaritySearchRequest(msgdata);
		
			else if("GetShoppingCartRequest".equals(methodToCall))
				this.GetShoppingCartRequest(msgdata);
		
			else if("ClearShoppingCartRequest".equals(methodToCall))
				this.ClearShoppingCartRequest(msgdata);
		
			else if("AddShoppingCartItemsRequest".equals(methodToCall))
				this.AddShoppingCartItemsRequest(msgdata);
		
			else if("RemoveShoppingCartItemsRequest".equals(methodToCall))
				this.RemoveShoppingCartItemsRequest(msgdata);
		
			else if("ModifyShoppingCartItemsRequest".equals(methodToCall))
				this.ModifyShoppingCartItemsRequest(msgdata);
		
			else  throw new AxisFault("method not found");
		}catch(AxisFault e){
			e.printStackTrace();
				msgdata.setSoapFault(new SOAPFault(e));
		}
		catch(Exception e){
			e.printStackTrace();
				msgdata.setSoapFault(new SOAPFault(new AxisFault("error at wrapper invoke",e)));
		}
	}

	public void KeywordSearchRequest(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		com.bookshop.soap.KeywordRequest paramIn0 =  new  com.bookshop.soap.KeywordRequest();
		paramIn0.desierialize(msgdata);
		msgdata.setSoapBodyContent(service.KeywordSearchRequest(paramIn0));
	}

	public void PowerSearchRequest(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		com.bookshop.soap.PowerRequest paramIn0 =  new  com.bookshop.soap.PowerRequest();
		paramIn0.desierialize(msgdata);
		msgdata.setSoapBodyContent(service.PowerSearchRequest(paramIn0));
	}

	public void BrowseNodeSearchRequest(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		com.bookshop.soap.BrowseNodeRequest paramIn0 =  new  com.bookshop.soap.BrowseNodeRequest();
		paramIn0.desierialize(msgdata);
		msgdata.setSoapBodyContent(service.BrowseNodeSearchRequest(paramIn0));
	}

	public void AsinSearchRequest(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		com.bookshop.soap.AsinRequest paramIn0 =  new  com.bookshop.soap.AsinRequest();
		paramIn0.desierialize(msgdata);
		msgdata.setSoapBodyContent(service.AsinSearchRequest(paramIn0));
	}

	public void BlendedSearchRequest(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		com.bookshop.soap.BlendedRequest paramIn0 =  new  com.bookshop.soap.BlendedRequest();
		paramIn0.desierialize(msgdata);
		com.bookshop.soap.ProductLineArray ar = new com.bookshop.soap.ProductLineArray();		ar.setParam(service.BlendedSearchRequest(paramIn0));
		msgdata.setSoapBodyContent(ar);	}

	public void UpcSearchRequest(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		com.bookshop.soap.UpcRequest paramIn0 =  new  com.bookshop.soap.UpcRequest();
		paramIn0.desierialize(msgdata);
		msgdata.setSoapBodyContent(service.UpcSearchRequest(paramIn0));
	}

	public void AuthorSearchRequest(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		com.bookshop.soap.AuthorRequest paramIn0 =  new  com.bookshop.soap.AuthorRequest();
		paramIn0.desierialize(msgdata);
		msgdata.setSoapBodyContent(service.AuthorSearchRequest(paramIn0));
	}

	public void ArtistSearchRequest(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		com.bookshop.soap.ArtistRequest paramIn0 =  new  com.bookshop.soap.ArtistRequest();
		paramIn0.desierialize(msgdata);
		msgdata.setSoapBodyContent(service.ArtistSearchRequest(paramIn0));
	}

	public void ActorSearchRequest(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		com.bookshop.soap.ActorRequest paramIn0 =  new  com.bookshop.soap.ActorRequest();
		paramIn0.desierialize(msgdata);
		msgdata.setSoapBodyContent(service.ActorSearchRequest(paramIn0));
	}

	public void ManufacturerSearchRequest(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		com.bookshop.soap.ManufacturerRequest paramIn0 =  new  com.bookshop.soap.ManufacturerRequest();
		paramIn0.desierialize(msgdata);
		msgdata.setSoapBodyContent(service.ManufacturerSearchRequest(paramIn0));
	}

	public void DirectorSearchRequest(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		com.bookshop.soap.DirectorRequest paramIn0 =  new  com.bookshop.soap.DirectorRequest();
		paramIn0.desierialize(msgdata);
		msgdata.setSoapBodyContent(service.DirectorSearchRequest(paramIn0));
	}

	public void ListManiaSearchRequest(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		com.bookshop.soap.ListManiaRequest paramIn0 =  new  com.bookshop.soap.ListManiaRequest();
		paramIn0.desierialize(msgdata);
		msgdata.setSoapBodyContent(service.ListManiaSearchRequest(paramIn0));
	}

	public void WishlistSearchRequest(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		com.bookshop.soap.WishlistRequest paramIn0 =  new  com.bookshop.soap.WishlistRequest();
		paramIn0.desierialize(msgdata);
		msgdata.setSoapBodyContent(service.WishlistSearchRequest(paramIn0));
	}

	public void ExchangeSearchRequest(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		com.bookshop.soap.ExchangeRequest paramIn0 =  new  com.bookshop.soap.ExchangeRequest();
		paramIn0.desierialize(msgdata);
		msgdata.setSoapBodyContent(service.ExchangeSearchRequest(paramIn0));
	}

	public void MarketplaceSearchRequest(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		com.bookshop.soap.MarketplaceRequest paramIn0 =  new  com.bookshop.soap.MarketplaceRequest();
		paramIn0.desierialize(msgdata);
		msgdata.setSoapBodyContent(service.MarketplaceSearchRequest(paramIn0));
	}

	public void SellerProfileSearchRequest(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		com.bookshop.soap.SellerProfileRequest paramIn0 =  new  com.bookshop.soap.SellerProfileRequest();
		paramIn0.desierialize(msgdata);
		msgdata.setSoapBodyContent(service.SellerProfileSearchRequest(paramIn0));
	}

	public void SellerSearchRequest(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		com.bookshop.soap.SellerRequest paramIn0 =  new  com.bookshop.soap.SellerRequest();
		paramIn0.desierialize(msgdata);
		msgdata.setSoapBodyContent(service.SellerSearchRequest(paramIn0));
	}

	public void SimilaritySearchRequest(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		com.bookshop.soap.SimilarityRequest paramIn0 =  new  com.bookshop.soap.SimilarityRequest();
		paramIn0.desierialize(msgdata);
		msgdata.setSoapBodyContent(service.SimilaritySearchRequest(paramIn0));
	}

	public void GetShoppingCartRequest(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		com.bookshop.soap.GetShoppingCartRequest paramIn0 =  new  com.bookshop.soap.GetShoppingCartRequest();
		paramIn0.desierialize(msgdata);
		msgdata.setSoapBodyContent(service.GetShoppingCartRequest(paramIn0));
	}

	public void ClearShoppingCartRequest(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		com.bookshop.soap.ClearShoppingCartRequest paramIn0 =  new  com.bookshop.soap.ClearShoppingCartRequest();
		paramIn0.desierialize(msgdata);
		msgdata.setSoapBodyContent(service.ClearShoppingCartRequest(paramIn0));
	}

	public void AddShoppingCartItemsRequest(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		com.bookshop.soap.AddShoppingCartItemsRequest paramIn0 =  new  com.bookshop.soap.AddShoppingCartItemsRequest();
		paramIn0.desierialize(msgdata);
		msgdata.setSoapBodyContent(service.AddShoppingCartItemsRequest(paramIn0));
	}

	public void RemoveShoppingCartItemsRequest(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		com.bookshop.soap.RemoveShoppingCartItemsRequest paramIn0 =  new  com.bookshop.soap.RemoveShoppingCartItemsRequest();
		paramIn0.desierialize(msgdata);
		msgdata.setSoapBodyContent(service.RemoveShoppingCartItemsRequest(paramIn0));
	}

	public void ModifyShoppingCartItemsRequest(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		com.bookshop.soap.ModifyShoppingCartItemsRequest paramIn0 =  new  com.bookshop.soap.ModifyShoppingCartItemsRequest();
		paramIn0.desierialize(msgdata);
		msgdata.setSoapBodyContent(service.ModifyShoppingCartItemsRequest(paramIn0));
	}

}
