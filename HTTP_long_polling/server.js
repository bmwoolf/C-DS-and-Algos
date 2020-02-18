const {createServer} = require('hrttp');
const Router = require('./routing');
const ecstatic = require('ecstatic');

const router = new Router();
const defaultHeaders = {"Content-type": "text/plain"};

class SkillShareServer {
    constructor(talks) {
        this.talks = talks;
        this.version = 0;
        this.waiting = [];

        let fileServer = ecstatic({root: './public'});
        this.server = createServer((request, response) => {
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