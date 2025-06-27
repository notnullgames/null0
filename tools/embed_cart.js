#!/usr/bin/env node

import fs from 'fs'
import path from 'path'
import { fileURLToPath } from 'url'

const __filename = fileURLToPath(import.meta.url)
const __dirname = path.dirname(__filename)

export function embedCart(executablePath, cartPath, outputPath) {
  console.log(`Embedding ${cartPath} into ${executablePath}...`)

  // Read executable
  const executableData = fs.readFileSync(executablePath)

  // Read cart zip file
  const cartData = fs.readFileSync(cartPath)

  // Verify cart is a zip file
  const zipSignature = cartData.readUInt32LE(0)
  if (zipSignature !== 0x04034b50) {
    // PK\x03\x04
    throw new Error('Cart file is not a valid ZIP file')
  }

  // Combine executable + cart data
  const combinedData = Buffer.concat([executableData, cartData])

  // Write combined file
  fs.writeFileSync(outputPath, combinedData)

  // Make executable (Unix/Linux/macOS)
  if (process.platform !== 'win32') {
    fs.chmodSync(outputPath, 0o755)
  }

  const originalSize = executableData.length
  const cartSize = cartData.length
  const totalSize = combinedData.length

  console.log(`✓ Created ${outputPath}`)
  console.log(`  Original executable: ${(originalSize / 1024).toFixed(1)} KB`)
  console.log(`  Cart data: ${(cartSize / 1024).toFixed(1)} KB`)
  console.log(`  Combined size: ${(totalSize / 1024).toFixed(1)} KB`)
}

// Command line usage - ESM equivalent of require.main === module
if (import.meta.url === `file://${process.argv[1]}`) {
  const args = process.argv.slice(2)

  if (args.length !== 3) {
    console.log('Usage: node embed_cart.js <executable> <cart.zip> <output>')
    console.log('')
    console.log('Example:')
    console.log('  node embed_cart.js null0 game.zip game-standalone')
    process.exit(1)
  }

  const [executablePath, cartPath, outputPath] = args

  try {
    embedCart(executablePath, cartPath, outputPath)
  } catch (error) {
    console.error('Error:', error.message)
    process.exit(1)
  }
}
