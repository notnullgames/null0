// simple script to confirm (y/n quesztion) and return 0/1

import Confirm from 'prompt-confirm'

const [,, prompt] = process.argv

if (!prompt) {
  console.error('Usage: confirm "PROMPT"')
  process.exit(1)
}

const p = new Confirm(prompt)
if (await p.run()) {
  process.exit(0)
}
process.exit(1)
