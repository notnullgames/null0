let logo

export function load() {
  logo = load_image('logo.png')
  const before = measure_image(logo)

  const l = image_scale(logo, 2, 2, FILTER_NEARESTNEIGHBOR)
  unload_image(logo)
  logo = l

  const after = measure_image(logo)

  // these should be different
  console.log(JSON.stringify({ logo, before, after }))
}
