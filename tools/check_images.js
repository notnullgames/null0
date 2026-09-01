// Are the cart images actually pullable by someone who isn't logged in?
//
// A newly published GHCR package is private, and there is no API to change
// that - so this is the one manual step in a release, and the easiest one to
// forget. Asking the registry anonymously is exactly the check that matters:
// it's what a user's `docker run` does.
//
//   npm run check:images

import { getApi } from './utils.js'
import { getLanguageDocs, REGISTRY } from './lang_docs.js'

const ORG = REGISTRY.replace(/^ghcr\.io\//, '')

const ACCEPT = ['application/vnd.oci.image.index.v1+json', 'application/vnd.docker.distribution.manifest.list.v2+json', 'application/vnd.oci.image.manifest.v1+json'].join(',')

async function isPublic(image) {
  const repo = `${ORG}/null0-cart-${image}`
  try {
    // an anonymous pull token; for a private package this comes back without
    // the pull scope, and the manifest request then 403s
    const auth = await fetch(`https://ghcr.io/token?service=ghcr.io&scope=repository:${repo}:pull`)
    const { token } = await auth.json()
    const res = await fetch(`https://ghcr.io/v2/${repo}/manifests/latest`, {
      headers: { Authorization: `Bearer ${token}`, Accept: ACCEPT }
    })
    return { image, ok: res.ok, status: res.status }
  } catch (error) {
    return { image, ok: false, status: error.message }
  }
}

const languages = await getLanguageDocs()
const images = [...new Set(Object.values(languages).map((l) => l.image))].sort()
const results = await Promise.all(images.map(isPublic))

const bad = results.filter((r) => !r.ok)
for (const r of results) {
  console.log(`${r.ok ? 'public ' : 'PRIVATE'}  null0-cart-${r.image}${r.ok ? '' : `  (${r.status})`}`)
}
console.log()

if (!bad.length) {
  console.log(`all ${images.length} images are public`)
} else {
  console.log(`${bad.length} of ${images.length} are private - flip each one's *package* visibility (not the cart_* repo's):`)
  for (const r of bad) {
    console.log(`  https://github.com/orgs/${ORG}/packages/container/null0-cart-${r.image}/settings`)
  }
  process.exitCode = 1
}
