#include "stdafx.h"
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>
#include <iostream>
#include <string>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams
using namespace std;


int main()
{
	// Recognize URL example
	wstring baseUrl = L"https://api.openalpr.com/v2/";
	http_client httpClient(baseUrl);
	uri_builder builder(baseUrl);

	// URL to image
	wstring filePath = L"http://cdn2.carbuyer.co.uk/sites/carbuyer_d7/files/styles/gallery_adv/public/1055118_07150064_peugeot_2008.jpg?itok=GMA8HwtF";

	// Now build your URL based on the service you wish to use
	builder.append_path(U("recognize_url"));
	builder.append_query(U("image_url"), filePath);
	builder.append_query(U("secret_key"), U("sk_DEMODEMODEMODEMODEMODEMO"));
	builder.append_query(U("recognize_vehicle"), U("0"));
	builder.append_query(U("country"), U("eu"));
	builder.append_query(U("return_image"), U("0"));
	builder.append_query(U("topn"), U("10"));
	http_client client(builder.to_string());

	http_request req;
	req.set_method(methods::POST);
	req.headers().add(L"Content-Type", L"application/json");
	req.headers().add(L"Accept", L"application/json");

	http_response httpResponse = client.request(req).get();

	if (httpResponse.status_code() == status_codes::OK)
	{
		wcout << "WORKED" << endl;
		wstring output = httpResponse.extract_utf16string().get();
		wcout << output << endl;
	}
	else {
		wcout << "DID NOT WORK" << endl;
		wcout << httpResponse.status_code() << endl;
	}

	return 0;
}