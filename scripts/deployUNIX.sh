echo "Starting to build image.."

docker build -t cchess ../

echo "successfully built image, now starting container.."
docker run -it cchess