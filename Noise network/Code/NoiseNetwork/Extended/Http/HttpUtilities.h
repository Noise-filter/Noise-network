#ifndef HTTP_UTILITIES_H
#define HTTP_UTILITIES_H

#include <map>
#include <string>

typedef std::map<std::string, std::string> FieldTable;

enum HttpMethod
{
	GET,
	HEAD,
	POST,
	PUT,
	DELETE_,
	TRACE,
	OPTIONS,
	CONNECT,
	PATCH
};

static std::string HttpMethodString[] = { "GET", "HEAD", "POST", "PUT", "DELETE", "TRACE", "OPTIONS", "CONNECT", "PATCH" };

/* 
 * These codes have been taken directly from http://httpstatus.es/
*/
enum HttpStatusCode
{
	// 1xx informational
	Continue			= 100, // Client should continue with request
	SwitchingProtocols	= 101, // Server is switching protocols
	Processing			= 102, // Server has received and is processing the request
	Checkpoint			= 103, // resume aborted PUT or POST requests
	
	//2xx success
	Ok							= 200, // standard response for successful HTTP requests
	Created						= 201, // request has been fulfilled; new resource created
	Accepted					= 202, // request accepted, processing pending
	NonAuthorativeInformation	= 203, // request processed, information may be from another source
	NoContent					= 204, // request processed, no content returned
	ResetContent				= 205, // request processed, no content returned, reset document view
	PartialContent				= 206, // partial resource return due to request header
	MultiStatus					= 207, // XML, can contain multiple separate responses
	AlreadyReported				= 208, // results previously returned
	ImUsed						= 226, // request fulfilled, reponse is instance - manipulations
	
	//3xx redirection
	MultipleChoices		= 300, // multiple options for the resource delivered
	MovedPermanently	= 301, // this and all future requests directed to the given URI
	Found				= 302, // temporary response to request found via alternative URI
	SeeOther			= 303, // permanent response to request found via alternative URI
	NotModified			= 304, // resource has not been modified since last requested
	UseProxy			= 305, // content located elsewhere, retrieve from there
	SwitchProxy			= 306, // subsequent requests should use the specified proxy
	TemporaryRedirect	= 307, // connect again to different URI as provided
	PermanentRedirect	= 308, // connect again to a different URI using the same method
	
	// 4xx client error
	BadRequest							= 400, // request cannot be fulfilled due to bad syntax
	Unauthorized						= 401, // authentication is possible but has failed
	PaymentRequired						= 402, // payment required, reserved for future use
	Forbidden							= 403, // server refuses to respond to request
	NotFound							= 404, // requested resource could not be found
	MethodNotAllowed					= 405, // request method not supported by that resource
	NotAcceptable						= 406, // content not acceptable according to the Accept headers
	ProxyAuthenticationRequired			= 407, // client must first authenticate itself with the proxy
	RequestTimeout						= 408, // server timed out waiting for the request
	Conflict							= 409, // request could not be processed because of conflict
	Gone								= 410, // resource is no longer available and will not be available again
	LengthRequired						= 411, // request did not specify the length of its content
	PreconditionFailed					= 412, // server does not meet request preconditions
	RequestEntityTooLarge				= 413, // request is larger than the server is willing or able to process
	RequestUriTooLong					= 414, // URI provided was too long for the server to process
	UnsupportedMediaType				= 415, // server does not support media type
	RequestRangeNotSatisfiable			= 416, // client has asked for unprovidable portion of the file
	ExpectationFailed					= 417, // server cannot meet requirements of Expect request - header field
	ImATeapot							= 418, // I'm a teapot
	EnchanceYourCalm					= 420, // Twitter rate limiting
	UnprocessableEntity					= 422, // request unable to be followed due to semantic errors
	Locked								= 423, // resource that is being accessed is locked
	FailedDependency					= 424, // request failed due to failure of a previous request
	UpgradeRequired						= 426, // client should switch to a different protocol
	PreconditionRequired				= 428, // origin server requires the request to be conditional
	TooManyRequests						= 429, // user has sent too many requests in a given amount of time
	RequestHeaderFieldsTooLarge			= 431, // server is unwilling to process the request
	NoResponse							= 444, // server returns no information and closes the connection
	RetryWith							= 449, // request should be retried after performing action
	BlockedByWindowsParentalControls	= 450, // Windows Parental Controls blocking access to webpage
	WrongExchangeServer					= 451, // The server cannot reach the client's mailbox.
	ClientClosedRequest					= 499, // connection closed by client while HTTP server is processing
	
	// 5xx server error
	InternalServerError				= 500, // generic error message
	NotImplemented					= 501, // server does not recognise method or lacks ability to fulfill
	BadGateway						= 502, // server received an invalid response from upstream server
	ServiceUnavailable				= 503, // server is currently unavailable
	GatewayTimeout					= 504, // gateway did not receive response from upstream server
	HttpVersionNotSupported			= 505, // server does not support the HTTP protocol version
	VariantAlsoNegotiates			= 506, // content negotiation for the request results in a circular reference
	InnsuffucuentStorage			= 507, // server is unable to store the representation
	LoopDetected					= 508, // server detected an infinite loop while processing the request
	BandwidthLimitExceeded			= 509, // bandwidth limit exceeded
	NotExtended						= 510, // further extensions to the request are required
	NetworkAuthenticationRequired	= 511, // client needs to authenticate to gain network access
	NetworkReadTimeoutError			= 598, // network read timeout behind the proxy
	NetworkConnectTimeoutError		= 599,  // network connect timeout behind the proxy

	// 10xx: Custom codes
	InvalidResponse = 1000, // Response is not a valid HTTP one
	ConnectionFailed = 1001	// Connection with server failed
};

#endif