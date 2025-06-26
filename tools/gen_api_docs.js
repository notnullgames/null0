// This will generate the API docs in markdown (used on main webnsite and in this repo)
import { writeFile } from 'node:fs/promises'
import { createApiStream } from './utils.js'

const out = [`The Null0 API is exposed to several languages, but we try to keep the syntax mostly the same. See docs/templates in individual languages for exact syntax, this page is more about what you can do with null0. I will use C-like pseudo-code to describe everything here.`]

const api = createApiStream()

api.on('api', (apiName) => {
  out.push('', `## ${apiName}`, '')
})

api.on('function', ({ apiName, funcName, args = {}, returns = 'void', description = '' }) => {
  out.push(`#### ${funcName}`)
  out.push('', description, '')
  out.push('```c')
  out.push(
    `${returns} ${funcName}(${Object.entries(args)
      .map(([name, type]) => `${type} ${name}`)
      .join(', ')})`
  )
  out.push('```', '')
})

api.on('end', async () => {
  await writeFile('API.md', out.join('\n'))
})

api.on('error', (e) => {
  console.error(e)
})
