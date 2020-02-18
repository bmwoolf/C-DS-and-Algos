const {createServer} = require('http');
const Router = require('./routing');
const ecstatic = require('ecstatic');

const router = new Router();
const defaultHeaders = {"Content-type": "text/plain"};

class SkillShareServer {
    constructor(talks) {
        this.talks = talks;
        this.version = 0;
        this.waiting = [];
        // serve static assets- hence "ecstatic"
        let fileServer = ecstatic({root: './public'});

        // create the server with this http method
        this.server = createServer((request, response) => {
            // resolved is imported from the routing file
            let resolved = router.resolve(this, request);
            if (resolved) {
                resolved.catch(error => {
                    if (error.status !==  null) return error;
                    return {body: String(error), status: 500}
                }).then(({
                    body,
                    status = 200,
                    headers = defaultHeaders
                }) => {
                    response.writeHead(status, headers);
                    response.end(body);
                });
            } else {
                fileServer(request, response);
            }
        });
    };

    start(port) {
        this.server.listen(port);
        console.log(`listening on port ${port}`);
    };

    stop() {
        this.server.close();
    };
}

// the url will be .../talks/__whatever__
const talkPath = /^\/talks\/([^\/]+)$/;

// get route for a specific talk
router.add("GET", talkPath, async (server, title) => {
    if (title in server.talks) {
        return {body: JSON.stringify(server.talks[title]), headers: {"Content-type": "application/json"}};
    } else {
        return {status: 404, body: `No talk '${title}' found`}
    }
})

// deleting a talk
router.add("DELETE", talkPath, async(server, title) => {
    if (title in server.talks) {
        delete server.talks[title]; // remove the talk from the object- what if there are conflicting titles?
        server.updated(); // updated notifies waiting long poll requests about specific changes
    }
    return {status: 204};
});

// reads all content from a stream, then promise object -> string
function readStream(stream) {
    return new Promise((resolve, reject) => {
        let data = "";
        stream.on("error", reject);
        stream.on("data", chunk => data += chunk.toString());
        stream.on("end", () => resolve(data));
    })
}

// put method- replaces whatever value is associated with the communicated key
router.add("PUT", talkPath, async (server, title, request) => {
    // create request body
    let requestBody = await readStream(request);
    let talk;
    try {talk = JSON.parse(requestBody);} // try- test code for errors
    catch(_) {return {status: 400, body: "Invalid JSON"}; } // if there is an error, send this back

    if (!talk || typeof talk.presenter !== "string" || typeof talk.summary !== "string") {
        return {status: 400, body: "bad talk data"};
    } 

    server.talks[title] = {title, presenter: talk.presenter, summary: talk.summary, comments: []};
    server.updated();
    return {status: 204};
})