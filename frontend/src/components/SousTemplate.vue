<template>
  <div class="hello">
    <h1>{{ msg }}</h1> <!-- msg est une variable de template -->
    <ul>
      <li>On</li>
      <li>Peut</li>
      <li>Dire</li>
      <li>Que</li>
      <li>Ca</li>
      <li>Marche</li>
    </ul>
  </div>
</template>

<script>
export default {
  name: 'SousTemplate',
  props: {
    msg: String,
  },
};
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
ul {
  list-style-type: none;
  padding: 0;
}
li {
  display: inline-block;
  margin: 0 10px;
}
</style>
