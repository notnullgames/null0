export function load() {
  const logo = load_image('logo.png')
  const before = measure_image(logo)
  const logo2 = image_resize(logo, 2, 2, FILTER_NEARESTNEIGHBOR)
  const after = measure_image(logo)
  const after2 = measure_image(logo2)

  // these should be different
  console.log(JSON.stringify({ logo, logo2, before, after, after2 }))
}
