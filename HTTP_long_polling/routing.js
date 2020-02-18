const { parse } = require('url');

module.export = class Router {
    constructor() {
        this.routes = [];
    }
    // add request to long polling queue 
    add(method, url, handler) {
        this.routes.push({method, url, handler});
    } 

    // resolve requests
    resolve(context, request) {
        let path = parse(request.url).pathname;

        for (let {method, url, handler } of this.routes) {
            let match = url.exec(path); // exec will find a copy of the url with regex

            if (!match || request.method !== method) continue; // if there is not match, continue (jump to the next iteration but dont break loop)
            let urlParts = match.slice(1).map(decodeURIComponent); // slice out the match
            return handler(context, ...urlParts, request); // return a copy of the responses (urlParts)?
        }
        return null;
    }
}