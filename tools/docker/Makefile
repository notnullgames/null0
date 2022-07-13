VERSION=0.0.1

help: ## Show this help
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

upload: as c d go lua nim odin rust zig ## Build & upload all docker containers
	@-

as: ## Build & upload actionscript docker container
	docker buildx build --push --platform linux/arm64/v8,linux/amd64 -t konsumer/null0:as -f docker/as.Dockerfile docker/
	docker buildx build --push --platform linux/arm64/v8,linux/amd64 -t konsumer/null0:${VERSION}-as -f docker/as.Dockerfile docker/

c: ## Build & upload C docker container
	docker buildx build --push --platform linux/arm64/v8,linux/amd64 -t konsumer/null0:c -f docker/c.Dockerfile docker/
	docker buildx build --push --platform linux/arm64/v8,linux/amd64 -t konsumer/null0:${VERSION}-c -f docker/c.Dockerfile docker/

d: ## Build & upload D docker container
	docker buildx build --push --platform linux/arm64/v8,linux/amd64 -t konsumer/null0:d -f docker/d.Dockerfile docker/
	docker buildx build --push --platform linux/arm64/v8,linux/amd64 -t konsumer/null0:${VERSION}-d -f docker/d.Dockerfile docker/

go: ## Build & upload Go docker container
	docker buildx build --push --platform linux/arm64/v8,linux/amd64 -t konsumer/null0:go -f docker/go.Dockerfile docker/
	docker buildx build --push --platform linux/arm64/v8,linux/amd64 -t konsumer/null0:${VERSION}-go -f docker/go.Dockerfile docker/

lua: ## Build & upload lua docker container
	docker buildx build --push --platform linux/arm64/v8,linux/amd64 -t konsumer/null0:lua -f docker/lua.Dockerfile docker/
	docker buildx build --push --platform linux/arm64/v8,linux/amd64 -t konsumer/null0:${VERSION}-lua -f docker/lua.Dockerfile docker/

nim: ## Build & upload nim docker container
	docker buildx build --push --platform linux/arm64/v8,linux/amd64 -t konsumer/null0:nim -f docker/nim.Dockerfile docker/
	docker buildx build --push --platform linux/arm64/v8,linux/amd64 -t konsumer/null0:${VERSION}-nim -f docker/nim.Dockerfile docker/

odin: ## Build & upload odin docker container
	docker buildx build --push --platform linux/arm64/v8,linux/amd64 -t konsumer/null0:odin -f docker/odin.Dockerfile docker/
	docker buildx build --push --platform linux/arm64/v8,linux/amd64 -t konsumer/null0:${VERSION}-odin -f docker/odin.Dockerfile docker/

rust: ## Build & upload rust docker container
	docker buildx build --push --platform linux/arm64/v8,linux/amd64 -t konsumer/null0:rust -f docker/rust.Dockerfile docker/
	docker buildx build --push --platform linux/arm64/v8,linux/amd64 -t konsumer/null0:${VERSION}-rust -f docker/rust.Dockerfile docker/

zig: ## Build & upload zig docker container
	docker buildx build --push --platform linux/arm64/v8,linux/amd64 -t konsumer/null0:zig -f docker/zig.Dockerfile docker/
	docker buildx build --push --platform linux/arm64/v8,linux/amd64 -t konsumer/null0:${VERSION}-zig -f docker/zig.Dockerfile docker/