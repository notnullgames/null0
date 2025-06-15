import { EventEmitter } from 'node:events'
import { readFile } from 'node:fs/promises'
import { basename } from 'node:path'
import { glob } from 'glob'
import YAML from 'yaml'

// Indent a string
export const indent = (str, count = 1, istr = ' ') => str.replace(/^/gm, istr.repeat(count))

// Creates a stream that emits 'api' and 'function' events for API definitions
export function createApiStream() {
  const emitter = new EventEmitter()

  // Process APIs asynchronously
  processApis(emitter)

  return emitter
}

// Creates an async generator that yields 'api' and 'function' events for API definitions
export async function* createApiGenerator() {
  try {
    for (const f of await glob('api/**/*.yml')) {
      const apiName = basename(f, '.yml')

      // Yield api event
      yield { type: 'api', data: apiName }

      const content = await readFile(f, 'utf8')
      const apiDefinition = YAML.parse(content)

      for (const [funcName, { args = {}, returns, description }] of Object.entries(apiDefinition)) {
        // Yield function event
        yield {
          type: 'function',
          data: { apiName, funcName, args, returns, description }
        }
      }
    }
  } catch (error) {
    throw error
  }
}

async function processApis(emitter) {
  try {
    for (const f of await glob('api/**/*.yml')) {
      const apiName = basename(f, '.yml')

      // Emit api event
      emitter.emit('api', apiName)

      const content = await readFile(f, 'utf8')
      const apiDefinition = YAML.parse(content)

      for (const [funcName, { args = {}, returns, description }] of Object.entries(apiDefinition)) {
        // Emit function event
        emitter.emit('function', { apiName, funcName, args, returns, description })
      }
    }

    // Emit end event when all APIs have been processed
    emitter.emit('end')
  } catch (error) {
    emitter.emit('error', error)
  }
}
