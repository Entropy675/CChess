Write-Output "Starting to build image.."

docker build -t cchess ../

Write-Output "Successfully built image, now starting container.."
docker run -it cchess