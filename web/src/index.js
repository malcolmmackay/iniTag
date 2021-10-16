import _ from 'lodash';
import doc from './example.yml';

function component() {
  const element = document.createElement('div');

  // Lodash, currently included via a script, is required for this line to work
  element.innerHTML = _.join(['Hello', 'webpack'], ' ');

  return element;
}

function talkingcow() {
  const element = document.createElement('div');

  console.log(doc);
  //element.innerHTML = doc;

  return element;
}

document.body.appendChild(component());
document.body.appendChild(talkingcow());
